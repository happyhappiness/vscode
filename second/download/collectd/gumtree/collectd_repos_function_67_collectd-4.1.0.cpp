static int
trim (dest, str)
     char **dest;
     const char *str;
{
  /* remove the leading and trailing "'" from str
     and store the result in dest */
  const char *end   = strrchr (str, '\'');
  size_t len	    = LT_STRLEN (str);
  char *tmp;

  LT_DLFREE (*dest);

  if (!end)
    return 1;

  if (len > 3 && str[0] == '\'')
    {
      tmp = LT_EMALLOC (char, end - str);
      if (!tmp)
	return 1;

      strncpy(tmp, &str[1], (end - str) - 1);
      tmp[len-3] = LT_EOS_CHAR;
      *dest = tmp;
    }
  else
    {
      *dest = 0;
    }

  return 0;
}