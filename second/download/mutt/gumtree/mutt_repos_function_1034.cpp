static int
crc_matches(const char *d, unsigned int crc)
{
  int off = sizeof (validate);
  unsigned int mycrc = 0;

  if (!d)
    return 0;

  restore_int(&mycrc, (unsigned char *) d, &off);

  return (crc == mycrc);
}