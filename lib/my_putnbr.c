/*
** EPITECH PROJECT, 2022
** malloc
** File description:
** my_putnbr
*/

#include <unistd.h>

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