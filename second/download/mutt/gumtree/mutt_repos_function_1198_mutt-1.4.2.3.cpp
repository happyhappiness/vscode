static void strip_trailing_dot (char *q)
{
  char *p = q;
  
  for (; *q; q++)
    p = q;
  
  if (*p == '.')
    *p = '\0';
}