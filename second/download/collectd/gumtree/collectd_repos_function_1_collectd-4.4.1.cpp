static int
strcmp (str1, str2)
     const char *str1;
     const char *str2;
{
  if (str1 == str2)
    return 0;
  if (str1 == 0)
    return -1;
  if (str2 == 0)
    return 1;

  for (;*str1 && *str2; ++str1, ++str2)
    {
      if (*str1 != *str2)
	break;
    }

  return (int)(*str1 - *str2);
}