char *mutt_concat_path (char *d, const char *dir, const char *fname, size_t l)
{
  const char *fmt = "%s/%s";
  
  if (!*fname || (*dir && dir[strlen(dir)-1] == '/'))
    fmt = "%s%s";
  
  snprintf (d, l, fmt, dir, fname);
  return d;
}