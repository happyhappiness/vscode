void mutt_str_adjust (char **p)
{
  if (!p || !*p) return;
  safe_realloc (p, strlen (*p) + 1);
}