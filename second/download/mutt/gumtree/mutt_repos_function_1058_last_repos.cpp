static unsigned char *
dump_char(char *c, unsigned char *d, int *off, int convert)
{
  return dump_char_size (c, d, off, mutt_strlen (c) + 1, convert);
}