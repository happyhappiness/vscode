const char *mutt_getnamebyvalue (int val, const struct mapping_t *map)
{
  int i;

  for (i=0; map[i].name; i++)
    if (map[i].value == val)
      return (map[i].name);
  return NULL;
}