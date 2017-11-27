static const char*
strrchr(str, ch)
     const char *str;
     int ch;
{
  const char *p, *q = 0;

  for (p = str; *p != LT_EOS_CHAR; ++p)
    {
      if (*p == (char) ch)
	{
	  q = p;
	}
    }

  return q;
}