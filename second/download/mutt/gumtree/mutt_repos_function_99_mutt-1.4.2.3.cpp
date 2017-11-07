static void quote_simple(char *tmp, size_t len, const char *p)
{
  int i = 0;
  
  tmp[i++] = '"';
  while (*p && i < len - 3)
  {
    if (*p == '\\' || *p == '"')
      tmp[i++] = '\\';
    tmp[i++] = *p++;
  }
  tmp[i++] = '"';
  tmp[i] = 0;
}