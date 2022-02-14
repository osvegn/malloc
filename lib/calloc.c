/*
** EPITECH PROJECT, 2022
** malloc
** File description:
** calloc
*/

#include "lib_malloc.h"

void *calloc(size_t nmemb, size_t size)
{
    char *ptr = malloc(nmemb * size);

    if (!ptr)
        return (NULL);
    for (size_t i = 0; i < nmemb * size; i++) {
        ptr[i] = '\0';
    }
    return (ptr);
}