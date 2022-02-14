/*
** EPITECH PROJECT, 2022
** malloc
** File description:
** malloc
*/

#include "lib_malloc.h"
#include <unistd.h>
#include <stdio.h>

static block_t *first = NULL;

void my_putnbr(int fd, int nbr);

size_t size_to_get(size_t s)
{
    size_t size = 0;

    while (size < s + sizeof(block_t) * 2) {
        size += getpagesize() * 2;
    }
    return (size);
}

block_t *get_end_block(void)
{
    block_t *tmp = first;

    while (tmp->next)
        tmp = tmp->next;
    return (tmp);
}

block_t *set_free_block(block_t *block, size_t real_size)
{
    block_t *next;

    next = block->allocated + block->size;
    next->allocated = next + sizeof(block_t);
    next->size = real_size - block->size - sizeof(block_t) * 2;
    next->next = block->next;
    next->prev = block;
    next->free = true;
    block->next = next;
    return (next);
}

block_t *find_free_space(size_t size)
{
    block_t *block = NULL;
    block_t *tmp = first;
    size_t real_size;

    while (tmp) {
        if (tmp->free == true && tmp->size == size) {
            tmp->free = false;
            return (tmp);
        }
        if (tmp->free == true && tmp->size > size + sizeof(block_t)) {
            tmp->free = false;
            return (tmp);
            // if (!block) {
            //     block = tmp;
            // } else if (block && block->size > tmp->size) {
            //     block = tmp;
            // }
        }
        tmp = tmp->next;
    }
    return (NULL);
}

block_t *create_first_block(size_t size)
{
    size_t real_size = size_to_get(size);
    block_t *block = sbrk(real_size);

    if ((void *)block == (void *)-1)
        return (NULL);
    block->allocated = block + sizeof(block_t);
    block->free = false;
    block->prev = NULL;
    block->size = size;
    block->next = set_free_block(block, real_size);
    first = block;
    return (block);
}

block_t *create_new_block(size_t size)
{
    size_t real_size = size_to_get(size);
    block_t *block = sbrk(real_size);

    if ((void *)block == (void *)-1)
        return (NULL);
    block->allocated = block + sizeof(block_t);
    block->free = false;
    block->prev = get_end_block();
    get_end_block()->next = block;
    block->size = size;
    block->next = set_free_block(block, real_size);
    return (block);
}

void draw_memory()
{
    block_t *tmp = first;
    size_t i = 0;

    while (tmp) {
        my_putnbr(1, i);
        write(1, " : ", 3);
        my_putnbr(1, tmp->size);
        write(1, " bytes ", 8);
        if (tmp->free) {
            write(1, "free\n", 5);
        } else {
            write(1, "used\n", 5);
        }
        // write(1, "->", 2);
        // my_putnbr(1, tmp);
        // write(1, "\n->", 3);
        // my_putnbr(1, tmp->allocated);
        // write(1, "\n", 1);
        tmp = tmp->next;
        i++;
    }
    write(1, "\n", 1);
}

void *malloc(size_t size)
{
    block_t *block = NULL;

    size += size % 2;
    if (!first) {
        block = create_first_block(size);
        return (block->allocated);
    }
    block = find_free_space(size);
    if (!block) {
        block = create_new_block(size);
        if (!block)
            return (NULL);
    }
    return (block->allocated);
}

void free(void *ptr)
{
    block_t *tmp = first;

    while (tmp->allocated != ptr && tmp->next)
        tmp = tmp->next;
    if (tmp->allocated == ptr) {
        tmp->free = true;
    }
}

void *calloc(size_t nmemb, size_t size)
{
    char *ptr = malloc(nmemb * size);

    if (!ptr)
        return (NULL);
    for (size_t i = 0; i < nmemb * size; i++) {
        ptr[i] = '\0';
    }
    return (ptr);
}
