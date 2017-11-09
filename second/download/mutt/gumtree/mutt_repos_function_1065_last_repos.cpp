static void
restore_buffer(BUFFER ** b, const unsigned char *d, int *off, int convert)
{
  unsigned int used;
  unsigned int offset;
  restore_int(&used, d, off);
  if (!used)
  {
    return;
  }

  *b = safe_malloc(sizeof (BUFFER));

  restore_char(&(*b)->data, d, off, convert);
  restore_int(&offset, d, off);
  (*b)->dptr = (*b)->data + offset;
  restore_int (&used, d, off);
  (*b)->dsize = used;
  restore_int (&used, d, off);
  (*b)->destroy = used;
}