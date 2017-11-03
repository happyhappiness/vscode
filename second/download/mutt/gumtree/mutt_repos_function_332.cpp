inline int ascii_tolower (int c)
{
  if (ascii_isupper (c))
    return c | 32;
  
  return c;
}