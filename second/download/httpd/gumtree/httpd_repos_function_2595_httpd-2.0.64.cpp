static unsigned long FASTCALL
hash(KEY s)
{
  unsigned long h = 0;
  while (*s)
    h = CHAR_HASH(h, *s++);
  return h;
}