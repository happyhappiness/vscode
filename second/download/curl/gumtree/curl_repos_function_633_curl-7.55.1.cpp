static void mydtor(void *p)
{
  int *ptr = (int *)p;
  free(ptr);
}