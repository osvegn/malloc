/*
** EPITECH PROJECT, 2022
** malloc
** File description:
** first_block
*/

#include "lib_malloc.h"

static block_t *first = NULL;

block_t *get_first_block(void)
{
    return (first);
}

void set_first_block(block_t *block)
{
    first = block;
}

block_t *get_end_block(void)
{
    block_t *tmp = first;

    while (tmp->next)
        tmp = tmp->next;
    return (tmp);
}