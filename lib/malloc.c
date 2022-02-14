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
void my_putstr(int fd, char *str);

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
    void *ptr;

    next = block->allocated + block->size;
    ptr = next;
    next->allocated = ptr + sizeof(block_t);
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
            if (!block) {
                block = tmp;
            } else if (block && block->size > tmp->size) {
                block = tmp;
            }
        }
        tmp = tmp->next;
    }
    if (block) {
        real_size = block->size + sizeof(block_t);
        block->free = false;
        block->size = size;
        block->next = set_free_block(block, real_size);
        return (block);
    }
    return (NULL);
}

block_t *create_first_block(size_t size)
{
    size_t real_size = size_to_get(size);
    block_t *block = sbrk(real_size);
    void *ptr = block;

    if ((void *)block == (void *)-1)
        return (NULL);
    block->allocated = ptr + sizeof(block_t);
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
    void *ptr = block;

    if ((void *)block == (void *)-1)
        return (NULL);
    block->allocated = ptr + sizeof(block_t);
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
/*
    my_putstr(1, "Print Memory :\n");
    while (tmp) {
        my_putstr(1, "\t");
        my_putnbr(1, i);
        my_putstr(1, " -> position block : ");
        my_putnbr(1, tmp);
        my_putstr(1, ", position memory : ");
        my_putnbr(1, tmp->allocated);
        my_putstr(1, " -> difference : ");
        my_putnbr(1, tmp->allocated - (char *)tmp);
        if (tmp->next) {
            my_putstr(1, " && ");
            my_putnbr(1, (char *)tmp->next - tmp->allocated);
        }
        my_putstr(1, " | size : ");
        my_putnbr(1, tmp->size);
        if (tmp->free) {
            my_putstr(1, " free\n");
        } else {
            my_putstr(1, " used\n");
        }
        tmp = tmp->next;
        i++;
    }
    write(1, "\n", 1);
    */
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
    draw_memory();
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

void *realloc(void *ptr, size_t size)
{
    block_t *tmp = first;
    block_t *new_block = first;
    char *value1;
    char *value2;
    void *nptr;

    if (!ptr) {
        return (malloc(size));
    }
    while (tmp && tmp->allocated != ptr) {
        tmp = tmp->next;
    }
    if (!tmp)
        return (NULL);
    if (ptr && size == 0) {
        free(ptr);
        return (NULL);
    }
    nptr = malloc(size);
    while (new_block && new_block->allocated != nptr)
        new_block = new_block->next;
    value1 = new_block->allocated;
    value2 = tmp->allocated;
    for (size_t index = 0; index < new_block->size && index < tmp->size; index++) {
        value1[index] = value2[index];
    }
    new_block->allocated = value1;
    free(ptr);
    return (new_block->allocated);
}
