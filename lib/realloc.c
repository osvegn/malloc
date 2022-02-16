/*
** EPITECH PROJECT, 2022
** malloc
** File description:
** realloc
*/

#include "lib_malloc.h"

block_t *find_ptr(void *ptr, block_t *tmp)
{
    while (tmp && tmp->allocated != ptr) {
        tmp = tmp->next;
    }
    return (tmp);
}

int size_of_zero(void *ptr, size_t size)
{
    if (ptr && size == 0) {
        free(ptr);
        return (-1);
    }
    return (1);
}

void copy_memory(block_t *new_block, block_t *tmp)
{
    char *value1;
    char *value2;

    value1 = new_block->allocated;
    value2 = tmp->allocated;
    for (size_t i = 0; i < new_block->size && i < tmp->size; i++) {
        value1[i] = value2[i];
    }
    new_block->allocated = value1;
}

void *realloc(void *ptr, size_t size)
{
    block_t *tmp = get_first_block();
    block_t *new_block = get_first_block();
    void *nptr;

    if (!ptr)
        return (malloc(size));
    tmp = find_ptr(ptr, tmp);
    if (!tmp)
        return (NULL);
    if (size_of_zero(ptr, size) < 0)
        return (NULL);
    nptr = malloc(size);
    new_block = find_ptr(nptr, new_block);
    copy_memory(new_block, tmp);
    free(ptr);
    return (new_block->allocated);
}
