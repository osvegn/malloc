/*
** EPITECH PROJECT, 2022
** malloc
** File description:
** find_free_space
*/

#include "lib_malloc.h"

block_t *find_better_block(block_t *better_block, block_t *block)
{
    if (!better_block) {
        better_block = block;
    } else if (better_block && better_block->size > block->size) {
        better_block = block;
    }
    return (better_block);
}

block_t *find_free_space(size_t size)
{
    block_t *block = NULL;
    size_t real_size = 0;

    for (block_t *tmp = get_first_block(); tmp; tmp = tmp->next) {
        if (tmp->free == true && tmp->size == size) {
            tmp->free = false;
            return (tmp);
        }
        if (tmp->free == true && tmp->size > size + sizeof(block_t))
            block = find_better_block(block, tmp);
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
