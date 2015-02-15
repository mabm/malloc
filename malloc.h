/*
** malloc.h for  in /home/jobertomeu/Work/malloc
** 
** Made by Joris Bertomeu
** Login   <jobertomeu@epitech.net>
** 
** Started on  Thu Feb  5 11:12:32 2015 Joris Bertomeu
** Last update Sun Feb 15 16:17:17 2015 Joris Bertomeu
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

#endif		/* _MALLOC_H_ */
