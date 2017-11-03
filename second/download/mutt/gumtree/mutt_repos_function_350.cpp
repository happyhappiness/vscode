static const char *find_ext_name(const char *key)
{
  int j;

  for (j = 0; ExtKeys[j].name; ++j)
  {
    if (strcasecmp(key, ExtKeys[j].name) == 0)
      return ExtKeys[j].sym;
  }
  return 0;
}