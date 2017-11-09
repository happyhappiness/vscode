static unsigned char *
dump_list(LIST * l, unsigned char *d, int *off, int convert)
{
  unsigned int counter = 0;
  unsigned int start_off = *off;

  d = dump_int(0xdeadbeef, d, off);

  while (l)
  {
    d = dump_char(l->data, d, off, convert);
    l = l->next;
    counter++;
  }

  memcpy(d + start_off, &counter, sizeof (int));

  return d;
}