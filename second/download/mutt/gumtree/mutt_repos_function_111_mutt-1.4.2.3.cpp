void mutt_str_adjust (char **p)
{
  if (!p || !*p) return;
  safe_realloc ((void **) p, strlen (*p) + 1);
}