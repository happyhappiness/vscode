static int address_uses_unicode(const char *a)
{
  if (!a)
    return 0;

  while (*a)
  {
    if ((unsigned char) *a & (1<<7))
      return 1;
    a++;
  }

  return 0;
}