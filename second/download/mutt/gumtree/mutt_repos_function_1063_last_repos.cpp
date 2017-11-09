static void
restore_list(LIST ** l, const unsigned char *d, int *off, int convert)
{
  unsigned int counter;

  restore_int(&counter, d, off);

  while (counter)
  {
    *l = safe_malloc(sizeof (LIST));
    restore_char(&(*l)->data, d, off, convert);
    l = &(*l)->next;
    counter--;
  }

  *l = NULL;
}