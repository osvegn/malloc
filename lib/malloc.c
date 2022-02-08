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

/* void *realloc(void *ptr, size_t size)
{
    char *nptr = malloc(size);
    char *tmp = ptr;

    if (!nptr)
        return (NULL);
    for (int i = 0; tmp[i] && i < size; i++) {
        nptr[i] = tmp[i];
    }
    free(ptr);
    return (nptr);
}

void *calloc(size_t nmemb, size_t size)
{
    write(1, "calloc\n", 7);
    char *ptr = malloc(nmemb * size);

    if (!ptr)
        return (NULL);
    for (size_t i = 0; i < nmemb * size; i++) {
        ptr[i] = '\0';
    }
    write(1, "end\n", 4);
    return (ptr);
}*/

void free(void *ptr)
{
    block_t *tmp = first;

    while (tmp->allocated != ptr && tmp->next)
        tmp = tmp->next;
    if (tmp->allocated == ptr) {
        tmp->free = true;
    }
}

size_t page_needed(size_t size)
{
    size_t tmp = 0;

    while (tmp < size)
        tmp += getpagesize() * 2;
    return (tmp);
}

block_t *first_block(size_t size)
{
    size_t page_size = page_needed(size);
    block_t *block = sbrk(page_size);
    block_t *next;

    if ((void *)block == (void*)-1)
        return (NULL);
    block->allocated = block + sizeof(block_t);
    block->free = false;
    block->prev = NULL;
    block->size = size;
    /* if (size != getpagesize()) {
        write(1, "a\n", 2);
        block->next = next;
        next->free = true;
        next->next = NULL;
        next->prev = block;
        next->size = page_size - sizeof(block_t) * 2 - size;
        next->allocated = block->allocated + block->size + sizeof(block_t);
        write(1, "a\n", 2);
    } else {
        block->next = NULL;
    } */
    block->next = NULL;
    first = block;
    return (block);
}

block_t *new_block(size_t size)
{
    size_t page_size = page_needed(size);
    block_t *block = sbrk(page_size);
    block_t *tmp = first;
    block_t *next;

    while (tmp->next)
        tmp = tmp->next;
    if ((void *)block == (void*)-1)
        return (NULL);
    tmp->next = block;
    block->allocated = block + sizeof(block_t);
    block->free = false;
    block->prev = tmp;
    block->size = size;
    /* if (size != getpagesize()) {
        write(1, "b\n", 2);
        block->next = next;
        next->free = true;
        next->next = NULL;
        next->prev = block;
        next->size = page_size - sizeof(block_t) * 2 - size;
        next->allocated = block->allocated + block->size + sizeof(block_t);
    } else {
        block->next = NULL;
    } */
    block->next = NULL;
    return (block);
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
    block = new_block(size);
    if (!block)
        return (NULL);
    return (block->allocated);
}