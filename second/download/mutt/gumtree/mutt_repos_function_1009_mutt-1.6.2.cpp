static void
restore_parameter(PARAMETER ** p, const unsigned char *d, int *off, int convert)
{
  unsigned int counter;

  restore_int(&counter, d, off);

  while (counter)
  {
    *p = safe_malloc(sizeof (PARAMETER));
    restore_char(&(*p)->attribute, d, off, 0);
    restore_char(&(*p)->value, d, off, convert);
    p = &(*p)->next;
    counter--;
  }

  *p = NULL;
}