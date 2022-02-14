/*
** EPITECH PROJECT, 2022
** malloc
** File description:
** create_block
*/

#include "lib_malloc.h"
#include <unistd.h>

size_t size_to_get(size_t size)
{
    size_t _size = 0;

    while (_size < size + sizeof(block_t) * 2) {
        _size += getpagesize() * 2;
    }
    return (_size);
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
    set_first_block(block);
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