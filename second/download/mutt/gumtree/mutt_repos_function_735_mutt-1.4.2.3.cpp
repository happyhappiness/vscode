static char *skip_ws (char *s)
{
  while (*s && isspace (*s))
    s++;

  return s;
}