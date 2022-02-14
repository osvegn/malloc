/*
** EPITECH PROJECT, 2022
** malloc
** File description:
** set_free_block
*/

#include "lib_malloc.h"

block_t *set_free_block(block_t *block, size_t real_size)
{
    block_t *next;
    void *ptr;

    next = (void *)block->allocated + block->size;
    ptr = next;
    next->allocated = ptr + sizeof(block_t);
    next->size = real_size - block->size - sizeof(block_t) * 2;
    next->next = block->next;
    next->prev = block;
    next->free = true;
    block->next = next;
    return (next);
}
