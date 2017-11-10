int
pcre_get_named_substring(const pcre *code, const char *subject, int *ovector,
  int stringcount, const char *stringname, const char **stringptr)
{
int n = pcre_get_stringnumber(code, stringname);
if (n <= 0) return n;
return pcre_get_substring(subject, ovector, stringcount, n, stringptr);
}