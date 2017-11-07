static int alias_SortAlias (const void *a, const void *b)
{
  ALIAS *pa = *(ALIAS **) a;
  ALIAS *pb = *(ALIAS **) b;
  int r = mutt_strcasecmp (pa->name, pb->name);

  return (RSORT (r));
}