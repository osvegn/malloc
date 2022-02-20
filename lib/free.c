/*
** EPITECH PROJECT, 2022
** malloc
** File description:
** free
*/

#include "lib_malloc.h"
#include <unistd.h>
#include <pthread.h>

void set_next_prev(block_t *tmp)
{
    if (tmp->next->next)
        tmp->next->next->prev = tmp;
}

void set_prev_next(block_t *tmp)
{
    if (tmp->prev)
        tmp->prev->next = NULL;
}

void move_break_point(block_t *tmp)
{
    void *ptr = NULL;

    while (tmp && tmp->free && tmp->size + sizeof(block_t) >=
        getpagesize() * 2) {
        if (tmp->size + sizeof(block_t) == getpagesize() * 2) {
            set_prev_next(tmp);
            tmp = NULL;
        } else
            tmp->size -= getpagesize() * 2;
        ptr = sbrk(-(getpagesize() * 2));
        if (ptr == (void *)-1)
            return;
        if (sbrk(0) == get_first_block()) {
            create_empty_block();
            return;
        }
    }
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
        } else
            tmp = tmp->next;
    }
    move_break_point(tmp);
}

void free(void *ptr)
{
    block_t *tmp = get_first_block();
    pthread_mutex_t mut = PTHREAD_MUTEX_INITIALIZER;

    pthread_mutex_lock(&mut);
    while (tmp->allocated != ptr && tmp->next)
        tmp = tmp->next;
    if (tmp->allocated == ptr) {
        tmp->free = true;
    }
    merge_free_space();
    pthread_mutex_unlock(&mut);
}
