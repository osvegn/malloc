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

size_t size_needed(size_t size)
{
    size_t tmp = 0;

    while (tmp < size + sizeof(block_t) * 2)
        tmp += getpagesize() * 2;
    return (tmp);
}

block_t *go_last_pointer(void)
{
    block_t *tmp = first;

    while (tmp->next)
        tmp = tmp->next;
    return (tmp);
}

block_t *setup_free_part_of_block(size_t page_size, block_t *block)
{
    block_t *next;

    next = block->allocated + block->size;
    next->free = true;
    next->next = NULL;
    next->prev = block;
    next->size = page_size - block->size - sizeof(block_t) * 2;
    next->allocated = next + sizeof(block_t);
    block->next = next;
    return (block);
}

block_t *first_block(size_t size)
{
    size_t total_size = size_needed(size);
    block_t *block = sbrk(total_size);

    if ((void *)block == (void*)-1)
        return (NULL);
    block->allocated = block + sizeof(block_t);
    block->free = false;
    block->prev = NULL;
    block->size = size;
    block->next = NULL;
    if (size != total_size) {
        block = setup_free_part_of_block(total_size, block);
    }
    first = block;
    return (block);
}

block_t *new_block(size_t size)
{
    size_t total_size = size_needed(size);
    block_t *block = sbrk(total_size);
    block_t *tmp = go_last_pointer();

    if ((void *)block == (void*)-1)
        return (NULL);
    tmp->next = block;
    block->allocated = block + sizeof(block_t);
    block->free = false;
    block->prev = tmp;
    block->size = size;
    block->next = NULL;
    if (size != total_size)
        block = setup_free_part_of_block(total_size, block);
    return (block);
}

block_t *is_better_space(block_t *block, block_t *better_block)
{
    if (!better_block)
        better_block = block;
    else if (better_block->size > block->size)
        better_block = block;
    return (better_block);
}

block_t *setup_available_space(block_t *block, size_t size)
{
    block_t *next;
    
    next = block->allocated + size;
    next->allocated = next + sizeof(block_t);
    next->free = true;
    next->next = block->next;
    next->prev = block;
    next->size = block->size - size - sizeof(block_t);
    block->next = next;
    block->size = size;
    block->free = false;
    return (block);
}

block_t *find_available_space(size_t size)
{
    block_t *tmp = first;
    block_t *better_block = NULL;

    while (tmp->next) {
        if (tmp->free == true && tmp->size == size) {
            tmp->free = false;
            return (tmp);
        }
        if (tmp->free == true && tmp->size - sizeof(block_t) > size) {
            //better_block = is_better_space(tmp, better_block);
        }
        tmp = tmp->next;
    }
    if (better_block != NULL) {
        better_block = setup_available_space(better_block, size);
        return (better_block);
    }
    return (NULL);
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

void draw_memory()
{
    block_t *tmp = first;
    int i = 1;

    while (tmp) {
        printf("%i : %i bytes", i, tmp->size);
        if (tmp->free)
            printf(" free\n", i);
        else
            printf(" used\n");
        i++;
        tmp = tmp->next;
    }
    write(1, "\n", 1);
}

void *malloc(size_t size)
{
    block_t *block = NULL;

    if (!first) {
        block = first_block(size);
        if (!block)
            return (NULL);
        return (block->allocated);
    }
    block = find_available_space(size);
    if (!block) {
        block = new_block(size);
        if (!block)
            return (NULL);
    }
    return (block->allocated);
}
