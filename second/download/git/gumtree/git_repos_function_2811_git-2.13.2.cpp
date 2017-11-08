static int
cmp_string (const void *pstr1, const void *pstr2)
{
  const char *str1 = *(const char **)pstr1;
  const char *str2 = *(const char **)pstr2;

  return strcmp (str1, str2);
}