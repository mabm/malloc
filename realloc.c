/*
** realloc.c for realloc in /home/barnea_v/rendu/PSU_2014_malloc
** 
** Made by Viveka BARNEAUD
** Login   <barnea_v@epitech.net>
** 
** Started on  Sun Feb 15 16:29:34 2015 Viveka BARNEAUD
** Last update Sun Feb 15 16:40:51 2015 Viveka BARNEAUD
*/

#include	<stddef.h>
#include	<string.h>
#include	"malloc.h"

void		*realloc(void *ptr, size_t size)
{
  void		*tmp;

  if (!ptr)
    return (malloc(size));
  if (!(tmp = malloc(size)))
    return (NULL);
  memcpy(tmp, ptr, ((t_header*) (ptr - sizeof(t_header)))->size);
  free(ptr);
  return (tmp);
}
