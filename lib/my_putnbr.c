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