/*
** EPITECH PROJECT, 2022
** malloc
** File description:
** lib_malloc
*/

#pragma once

#include <stddef.h>
#include <stdbool.h>

typedef struct block_s {
    struct block_s *next;
    struct block_s *prev;
    size_t size;
    bool free;
    char *allocated;
} block_t;

void *malloc(size_t size);
void free(void *ptr);
void *calloc(size_t nmemb, size_t size);
void *realloc(void *ptr, size_t size);
void *reallocarray(void *ptr, size_t nmemb, size_t size);

block_t *get_first_block(void);
void set_first_block(block_t *block);
block_t *get_end_block(void);

block_t *find_better_block(block_t *block, block_t *tmp);
block_t *find_free_space(size_t size);

block_t *set_free_block(block_t *block, size_t real_size);

block_t *create_first_block(size_t size);
block_t *create_new_block(size_t size);
block_t *create_empty_block(void);
