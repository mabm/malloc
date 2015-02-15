/*
** calloc.c for calloc in /home/barnea_v/rendu/PSU_2014_malloc
** 
** Made by Viveka BARNEAUD
** Login   <barnea_v@epitech.net>
** 
** Started on  Sun Feb 15 16:29:05 2015 Viveka BARNEAUD
** Last update Sun Feb 15 16:40:52 2015 Viveka BARNEAUD
*/

#include	<strings.h>
#include	<stddef.h>
#include	"malloc.h"

size_t		calc_requested_size(size_t size)
{
  size_t	ret = getpagesize();

  while (ret < size)
    ret += getpagesize();
  return (ret);
}

void		*calloc(size_t nmemb, size_t size)
{
  void		*ptr;

  if (!(ptr = malloc(nmemb * size)))
    return (NULL);
  bzero(ptr, nmemb * size);
  return (ptr);
}
