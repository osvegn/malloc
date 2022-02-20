/*
** EPITECH PROJECT, 2022
** malloc
** File description:
** malloc
*/

#include "lib_malloc.h"
#include <unistd.h>
#include <pthread.h>
#include <stdlib.h>

void *my_malloc(size_t size)
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

void *malloc(size_t size)
{
    void *ptr = NULL;
    pthread_mutex_t mut = PTHREAD_MUTEX_INITIALIZER;

    pthread_mutex_lock(&mut);
    ptr = my_malloc(size);
    pthread_mutex_unlock(&mut);
    return (ptr);
}
