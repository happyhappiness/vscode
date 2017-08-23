static inline char* realpath(const char* path, char* resolved_path)
{
  const size_t maxlen = KWSYS_SYSTEMTOOLS_MAXPATH;
  snprintf(resolved_path, maxlen, "%s", path);
  BPath normalized(resolved_path, NULL, true);
  const char* resolved = normalized.Path();
  if (resolved != NULL) // NULL == No such file.
  {
    if (snprintf(resolved_path, maxlen, "%s", resolved) < maxlen) {
      return resolved_path;
    }
  }
  return NULL; // something went wrong.
}