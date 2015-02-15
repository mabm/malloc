/*
** malloc.h for  in /home/jobertomeu/Work/malloc
** 
** Made by Joris Bertomeu
** Login   <jobertomeu@epitech.net>
** 
** Started on  Thu Feb  5 11:12:32 2015 Joris Bertomeu
** Last update Sun Feb 15 16:40:43 2015 Viveka BARNEAUD
*/

#ifndef		_MALLOC_H_
# define	_MALLOC_H_

# include	<unistd.h>
# include	<stdlib.h>
# include	<stdio.h>
# include	<string.h>
# include	<math.h>
# include	<pthread.h>

typedef	struct	s_malloc
{
  size_t	size;
  void		*ptr;
  void		*next;
}		t_malloc;

typedef struct	s_header
{
  int		size;
}		t_header;

size_t		calc_requested_size(size_t size);
void		*calloc(size_t nmemb, size_t size);
void		*realloc(void *ptr, size_t size);
void		*new_alloc(size_t size);
void		*crop_in_freep(size_t size, t_malloc *ptr);
void		*search_in_freep(size_t size);
void		*malloc(size_t size);
void		free(void *ptr);

#endif		/* _MALLOC_H_ */
