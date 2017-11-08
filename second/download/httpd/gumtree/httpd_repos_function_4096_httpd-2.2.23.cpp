int
pcre_copy_named_substring(const pcre *code, const char *subject, int *ovector,
  int stringcount, const char *stringname, char *buffer, int size)
{
int n = pcre_get_stringnumber(code, stringname);
if (n <= 0) return n;
return pcre_copy_substring(subject, ovector, stringcount, n, buffer, size);
}