static char **split_str (char *str)
{
  char **res, *lasts, *s;
  int  i;

  for (i = 2, s = strchr(str,','); s; i++)
     s = strchr(++s,',');

  res = calloc(i, sizeof(char*));
  if (!res)
    return NULL;

  for (i = 0, s = strtok_r(str, ",", &lasts); s;
       s = strtok_r(NULL, ",", &lasts), i++)
    res[i] = s;
  return res;
}