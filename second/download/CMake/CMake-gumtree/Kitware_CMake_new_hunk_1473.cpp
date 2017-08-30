#ifdef DEBUG

  printf("<== th_read_internal(): returning %d\n", i);

#endif

  return (int)i;

}





/* wrapper function for th_read_internal() to handle GNU extensions */

int

th_read(TAR *t)

{

  ssize_t i, j;

  size_t sz;

  char *ptr;



