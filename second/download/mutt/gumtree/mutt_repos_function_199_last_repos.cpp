const char *mutt_basename (const char *f)
{
  const char *p = strrchr (f, '/');
  if (p)
    return p + 1;
  else
    return f;
}