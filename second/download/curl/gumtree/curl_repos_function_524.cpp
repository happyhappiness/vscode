static int new_fnmatch(const char *pattern, const char *string)
{
  (void)pattern;
  (void)string;
  return CURL_FNMATCHFUNC_MATCH;
}