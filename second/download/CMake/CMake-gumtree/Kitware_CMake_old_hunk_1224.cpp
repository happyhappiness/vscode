  snprintf(resolved_path, maxlen, "%s", path);
  BPath normalized(resolved_path, NULL, true);
  const char *resolved = normalized.Path();
  if (resolved != NULL)   // NULL == No such file. 
    {
    if (snprintf(resolved_path, maxlen, "%s", resolved) < maxlen) 
      {
      return resolved_path;
      }
