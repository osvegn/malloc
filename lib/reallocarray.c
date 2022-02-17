/*
** EPITECH PROJECT, 2022
** malloc
** File description:
** reallocarray
*/

#include "lib_malloc.h"

void *reallocarray(void *ptr, size_t nmemb, size_t size)
{
    return (realloc(ptr, size * nmemb));
}
