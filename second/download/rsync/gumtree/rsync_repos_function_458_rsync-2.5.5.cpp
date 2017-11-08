int
fnmatch (pattern, string, flags)
     const char *pattern;
     const char *string;
     int flags;
{
  return internal_fnmatch (pattern, string, flags & FNM_PERIOD, flags);
}