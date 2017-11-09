int vsnprintf (char *str, size_t count, const char *fmt, va_list args)
{
  str[0] = 0;
  return(dopr(str, count, fmt, args));
}