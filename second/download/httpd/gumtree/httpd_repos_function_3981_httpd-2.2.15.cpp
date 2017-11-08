static int
pcre_posix_error_code(const char *s)
{
size_t i;
for (i = 0; i < sizeof(estring)/sizeof(char *); i++)
  if (strcmp(s, estring[i]) == 0) return eint[i];
return REG_ASSERT;
}