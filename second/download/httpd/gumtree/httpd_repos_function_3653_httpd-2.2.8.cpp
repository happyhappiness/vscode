static void
adjust_recurse(uschar *group, int adjust, BOOL utf8, compile_data *cd)
{
uschar *ptr = group;
while ((ptr = (uschar *)find_recurse(ptr, utf8)) != NULL)
  {
  int offset = GET(ptr, 1);
  if (cd->start_code + offset >= group) PUT(ptr, 1, offset + adjust);
  ptr += 1 + LINK_SIZE;
  }
}