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
    void *allocated;
} block_t;

void *malloc(size_t size);
void free(void *ptr);
/* void *calloc(size_t nmemb, size_t size);
void *realloc(void *ptr, size_t size);
void *reallocarray(void *ptr, size_t nmemb, size_t size); */