/*
** EPITECH PROJECT, 2022
** malloc
** File description:
** malloc
*/

#include "lib_malloc.h"
#include <unistd.h>
#include <stdio.h>
#include <pthread.h>
#include <stdlib.h>

void *malloc(size_t size)
{
    block_t *block = NULL;
    size_t i = 0;

    for (i = 1; i < size; i *= 2);
    size = i;
    if (!get_first_block()) {
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
