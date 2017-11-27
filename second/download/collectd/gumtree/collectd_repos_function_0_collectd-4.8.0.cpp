static char *
strdup(str)
     const char *str;
{
  char *tmp = 0;

  if (str)
    {
      tmp = LT_DLMALLOC (char, 1+ strlen (str));
      if (tmp)
	{
	  strcpy(tmp, str);
	}
    }

  return tmp;
}