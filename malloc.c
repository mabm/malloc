/*
** main.c for  in /home/jobertomeu/Work/malloc
** 
** Made by Joris Bertomeu
** Login   <jobertomeu@epitech.net>
** 
** Started on  Thu Feb  5 11:11:33 2015 Joris Bertomeu
** Last update Sun Feb 15 16:43:03 2015 Viveka BARNEAUD
*/

#include	"malloc.h"

static		t_malloc	*g_freep = NULL;

void		*new_alloc(size_t size)
{
  void		*ptr;
  t_malloc	*nodef;
  t_malloc	*tmpf;
  size_t	request;

  tmpf = g_freep;
  request = calc_requested_size(size);
  ptr = sbrk(request);
  nodef = ptr;
  ptr += sizeof(t_malloc);
  while (tmpf && tmpf->next)
    tmpf = tmpf->next;
  if (ptr - sizeof(t_malloc) == (void*) -1)
    _exit(127);
  ((t_header*) ptr)->size = size - (sizeof(t_header) + sizeof(t_malloc));
  nodef->size = request - size;
  nodef->ptr = ptr - sizeof(t_malloc) + size;
  nodef->next = NULL;
  if (!g_freep)
    g_freep = nodef;
  else
    tmpf->next = nodef;
  return (ptr + sizeof(t_header));
}

void		*crop_in_freep(size_t size, t_malloc *ptr)
{
  ptr->ptr += sizeof(t_malloc);
  ((t_header*) ptr->ptr)->size = size - (sizeof(t_header) + sizeof(t_malloc));
  ptr->size -= size;
  ptr->ptr += size - sizeof(t_malloc);
  return (ptr->ptr - size + sizeof(t_malloc) + sizeof(t_header));
}

void		*search_in_freep(size_t size)
{
  t_malloc	*tmp;

  tmp = g_freep;
  while (tmp)
    {
      if (tmp->size >= size)
     	return (crop_in_freep(size, tmp));
      tmp = tmp->next;
    }
  return (new_alloc(size));
}

void		*malloc(size_t size)
{
  void	*ptr;

  if (!size)
    return (NULL);
  size = size + sizeof(t_header) + sizeof(t_malloc);
  if (!g_freep)
    ptr = new_alloc(size);
  else
    ptr = search_in_freep(size);
  return (ptr);
}

void		free(void *ptr)
{
  t_malloc	*tmp;
  int		size = 0;

  if (!ptr)
    return;
  size = ((t_header*) (ptr - sizeof(t_header)))->size + sizeof(t_header);
  tmp = g_freep;
  while (tmp && tmp->next)
    {
      if (ptr - sizeof(t_header) == tmp->ptr - size)
	{
	  tmp->size += size;
	  tmp->ptr -= size + sizeof(t_malloc);
	  return;
	}
      tmp = tmp->next;
    }
  tmp->next = ptr - sizeof(t_malloc) - sizeof(t_header);
  ((t_malloc*) tmp->next)->size = size;
  ((t_malloc*) tmp->next)->ptr = ptr - sizeof(t_header);
  ((t_malloc*) tmp->next)->next = NULL;
}
