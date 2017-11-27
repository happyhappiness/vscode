static const char*
strchr(str, ch)
     const char *str;
     int ch;
{
  const char *p;

  for (p = str; *p != (char)ch && *p != LT_EOS_CHAR; ++p)
    /*NOWORK*/;

  return (*p == (char)ch) ? p : 0;
}