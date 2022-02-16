/*
** EPITECH PROJECT, 2022
** malloc
** File description:
** my_putnbr
*/

#include <unistd.h>
#include "lib_malloc.h"

int my_putnbr(int fd, int nbr)
{
    char tmp = 0;

    if (nbr < 0) {
        write(fd, "-", 1);
        nbr *= -1;
    }
    if (nbr > 9) {
        my_putnbr(fd, nbr / 10);
    }
    tmp = nbr % 10 + '0';
    write(fd, &tmp, 1);
    return (0);
}

int my_strlen(char *str)
{
    int len = 0;

    if (str == NULL) {
        return (-1);
    }
    while (str[len]) {
        len++;
    }
    return (len);
}

int my_putstr(int fd, char *str)
{
    if (str == NULL)
        return (-1);
    write(fd, str, my_strlen(str));
    return (0);
}

// void draw_memory()
// {
//     block_t *tmp = get_first_block();
//     size_t i = 0;

//     my_putstr(1, "Print Memory :\n");
//     while (tmp) {
//         my_putstr(1, "\t");
//         my_putnbr(1, i);
//         my_putstr(1, " -> position block : ");
//         my_putnbr(1, tmp);
//         my_putstr(1, ", position memory : ");
//         my_putnbr(1, tmp->allocated);
//         my_putstr(1, " -> difference : ");
//         my_putnbr(1, tmp->allocated - (char *)tmp);
//         if (tmp->next) {
//             my_putstr(1, " && ");
//             my_putnbr(1, (char *)tmp->next - tmp->allocated);
//         }
//         my_putstr(1, " | size : ");
//         my_putnbr(1, tmp->size);
//         if (tmp->free) {
//             my_putstr(1, " free\n");
//         } else {
//             my_putstr(1, " used\n");
//         }
//         tmp = tmp->next;
//         i++;
//     }
//     write(1, "\n", 1);
// }