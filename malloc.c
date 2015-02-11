/*
** main.c for  in /home/jobertomeu/Work/malloc
** 
** Made by Joris Bertomeu
** Login   <jobertomeu@epitech.net>
** 
** Started on  Thu Feb  5 11:11:33 2015 Joris Bertomeu
** Last update Wed Feb 11 14:57:31 2015 Viveka BARNEAUD
*/

#include	<math.h>
#include	<pthread.h>
#include	"malloc.h"

static		t_malloc	*freep = NULL;
static		pthread_mutex_t	mutex_malloc = PTHREAD_MUTEX_INITIALIZER;

/* void		show_list(t_malloc *ptr, char *str) */
/* { */
/*   t_malloc	*tmp = ptr; */

/*   printf("---------- %s ----------\n", str); */
/*   while (tmp) */
/*     { */
/*       printf("Size :\t\t%d\n", tmp->size); */
/*       printf("Origi:\t\t%d\n", tmp->original); */
/*       printf("Ptr. :\t\t%p\n", tmp->ptr); */
/*       printf("Next :\t\t%p\n", tmp->next); */
/*       tmp = tmp->next; */
/*       printf("-------\n"); */
/*     } */
/* } */

void	my_putchar(char c)
{
  write(1, &c, 1);
}

void    my_put_nbr(int nb)
{
  int   neg;

  return;
  neg = 0;
  if (nb < 0)
    {
      my_putchar('-');
      if (nb == -2147483648)
        {
          neg = 1;
          nb++;
        }
      nb = nb * -1;
    }
  if (nb >= 10)
    my_put_nbr(nb / 10);
  if (neg == 1)
    {
      neg = 0;
      my_putchar(nb % 10 + '1');
    }
  else
    my_putchar(nb % 10 + '0');
}

size_t		calc_requested_size(size_t size)
{
  size_t	ret = getpagesize();

  while (ret < size)
    ret += getpagesize();
  return (ret);
}

void		my_write(char *str)
{
  write(1, str, strlen(str));
}

void		*new_alloc(size_t size)
{
  void		*ptr;
  t_malloc	*nodef;
  t_malloc	*tmpf;
  size_t	request;

  tmpf = freep;
  request = calc_requested_size(size);
  pthread_mutex_lock(&mutex_malloc);
  nodef = sbrk(sizeof(t_malloc));
  brk(nodef + sizeof(t_malloc));
  ptr = sbrk(request);
  pthread_mutex_unlock(&mutex_malloc);
  while (tmpf && tmpf->next)
    tmpf = tmpf->next;
  if (ptr == (void*) -1)
    _exit(127);
  ((t_header*) ptr)->size = size - sizeof(t_header);
  nodef->size = request - size;
  nodef->ptr = ptr + size;
  nodef->next = NULL;
  nodef->original = request;
  if (!freep)
    freep = nodef;
  else
    tmpf->next = nodef;
  return (ptr + sizeof(t_header));
}

void		*crop_in_freep(size_t size, t_malloc *ptr)
{
  void		*tmp = ptr->ptr;

  ((t_header*) tmp)->size = size - sizeof(t_header);
  ptr->size -= size;
  ptr->ptr = ptr->ptr + size;
  return (ptr->ptr - size + sizeof(t_header));
}

void		*search_in_freep(size_t size)
{
  t_malloc	*tmp;

  tmp = freep;
  while (tmp)
    {
      if (tmp->size >= size) {
     	return (crop_in_freep(size, tmp));
      }
      tmp = tmp->next;
    }
  return (new_alloc(size));
}

size_t	get_real_size(size_t size)
{
  float	i = 1;

  while (i <= size) {
    i = pow(i, 2);
  }
  return (i);
}

void	*malloc(size_t size)
{
  void	*ptr;

  if (!size)
    return (NULL);
  size = size + sizeof(t_header);
  if (!freep)
    ptr = new_alloc(size);
  else
    ptr = search_in_freep(size);
  return (ptr);
}

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

void		*calloc(size_t nmemb, size_t size)
{
  void		*ptr;

  if (!(ptr = malloc(nmemb * size)))
    return (NULL);
  bzero(ptr, nmemb * size);
  return (ptr);
}

void		free(void *ptr)
{
  t_malloc	*tmp;
  int		size = 0;

  if (!ptr)
    return;
  size = ((t_header*) (ptr - sizeof(t_header)))->size + sizeof(t_header);
  tmp = freep;
  while (tmp && tmp->next) {
    if (ptr - sizeof(t_header) == tmp->ptr - size) {
      tmp->size += size;
      tmp->ptr -= size;
      return;
    }
    tmp = tmp->next;
  }
  pthread_mutex_lock(&mutex_malloc);
  tmp->next = sbrk(sizeof(t_malloc));
  brk(tmp->next + sizeof(t_malloc));
  pthread_mutex_unlock(&mutex_malloc);
  ((t_malloc*) tmp->next)->size = size;
  ((t_malloc*) tmp->next)->original = -1;
  ((t_malloc*) tmp->next)->ptr = ptr - sizeof(t_header);
  ((t_malloc*) tmp->next)->next = NULL;
  //my_write("FREE END\n");
}

/* int	main() */
/* { */
/*   int	start = 10, size = start + 2, incr = 1; */
/*   void	*foo[size]; */
/*   int	i = 0; */

/*   foo[i] = malloc(50); */
/*   //my_write("APRES MALLOC\n"); */
/*   memset(foo[i], 0, 50); */
/*   memset(foo[i], 'o', 49); */
/*   //my_write("APRES MALLOC 2\n"); */
/*   /\* foo[i] = realloc(foo[i], 100); *\/ */
/*   /\* //printf("%s\n", foo[i]); *\/ */
/*   /\* memset(foo[i], 0, 100); *\/ */
/*   /\* memset(foo[i], 'o', 99); *\/ */
/*   /\* free(foo[i]); *\/ */
/*   /\* exit(0); *\/ */
/*   /\* for (i = start; i < size; i += incr) { *\/ */
/*   /\*   foo[i] = malloc(i); *\/ */
/*   /\*   memset(foo[i], 0, i); *\/ */
/*   /\*   memset(foo[i], 'o', i - 1); *\/ */
/*   /\*   foo[i] = realloc(foo[i], i + 50); *\/ */
/*   /\*   //printf("%s\n", foo[i]); *\/ */
/*   /\*   memset(foo[i], 0, i + 50); *\/ */
/*   /\*   memset(foo[i], 'o', (i + 50) - 1); *\/ */
/*   /\* } *\/ */
/*   /\* /\\* show_list(freep, "Freep"); *\\/ *\/ */
/*   /\* for (i = start; i < size; i += incr) { *\/ */
/*   /\*   free(foo[i]); *\/ */
/*   /\* } *\/ */
/*   /\* printf("\n"); *\/ */
/*   /\* show_list(freep, "Freep"); *\/ */
/* } */
