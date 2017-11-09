static char *skip_ws (char *s)
{
  while (*s && isspace ((unsigned char) *s))
    s++;

  return s;
}