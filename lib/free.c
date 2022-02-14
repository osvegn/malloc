/*
** EPITECH PROJECT, 2022
** malloc
** File description:
** free
*/

#include "lib_malloc.h"
#include <unistd.h>

void set_next_prev(block_t *tmp)
{
    if (tmp->next->next)
        tmp->next->next->prev = tmp;
}

void merge_free_space(void)
{
    block_t *tmp = get_first_block();
    void *ptr = NULL;

    while (tmp && tmp->next) {
        if (tmp->free && tmp->next->free) {
            tmp->size += tmp->next->size + sizeof(block_t);
            set_next_prev(tmp);
            tmp->next = tmp->next->next;
        } else {
            tmp = tmp->next;
        }
    }
    while (tmp && tmp->free && tmp->size + sizeof(block_t) >= getpagesize() * 2) {
        tmp->size -= getpagesize() * 2;
        ptr = sbrk(-(getpagesize() * 2));
        if (ptr == (void *)-1)
            return;
        if (sbrk(0) == get_first_block())
            return;
    }
}

void free(void *ptr)
{
    block_t *tmp = get_first_block();

    while (tmp->allocated != ptr && tmp->next)
        tmp = tmp->next;
    if (tmp->allocated == ptr) {
        tmp->free = true;
    }
    merge_free_space();
    //draw_memory();
}