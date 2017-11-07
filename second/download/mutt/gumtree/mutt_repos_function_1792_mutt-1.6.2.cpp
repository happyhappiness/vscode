const char *
_nl_normalize_codeset (codeset, name_len)
     const char *codeset;
     size_t name_len;
{
  int len = 0;
  int only_digit = 1;
  char *retval;
  char *wp;
  size_t cnt;

  for (cnt = 0; cnt < name_len; ++cnt)
    if (isalnum ((unsigned char) codeset[cnt]))
      {
	++len;

	if (isalpha ((unsigned char) codeset[cnt]))
	  only_digit = 0;
      }

  retval = (char *) malloc ((only_digit ? 3 : 0) + len + 1);

  if (retval != NULL)
    {
      if (only_digit)
	wp = stpcpy (retval, "iso");
      else
	wp = retval;

      for (cnt = 0; cnt < name_len; ++cnt)
	if (isalpha ((unsigned char) codeset[cnt]))
	  *wp++ = tolower ((unsigned char) codeset[cnt]);
	else if (isdigit ((unsigned char) codeset[cnt]))
	  *wp++ = codeset[cnt];

      *wp = '\0';
    }

  return (const char *) retval;
}