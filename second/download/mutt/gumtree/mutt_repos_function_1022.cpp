static unsigned char *
dump_address(ADDRESS * a, unsigned char *d, int *off, int convert)
{
  unsigned int counter = 0;
  unsigned int start_off = *off;

  d = dump_int(0xdeadbeef, d, off);

  while (a)
  {
#ifdef EXACT_ADDRESS
    d = dump_char(a->val, d, off, convert);
#endif
    d = dump_char(a->personal, d, off, convert);
    d = dump_char(a->mailbox, d, off, 0);
    d = dump_int(a->group, d, off);
    a = a->next;
    counter++;
  }

  memcpy(d + start_off, &counter, sizeof (int));

  return d;
}