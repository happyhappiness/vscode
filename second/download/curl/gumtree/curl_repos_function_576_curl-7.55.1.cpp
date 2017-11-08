static int new_fnmatch(void *ptr,
                       const char *pattern, const char *string)
{
  (void)ptr;
  (void)pattern;
  (void)string;
  return CURL_FNMATCHFUNC_MATCH;
}