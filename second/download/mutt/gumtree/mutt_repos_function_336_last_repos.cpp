inline int ascii_toupper (int c)
{
  if (ascii_islower (c))
    return c & ~32;
  
  return c;
}