static int empty_group (group_t *g)
{
  if (!g)
    return -1;
  return !g->as && !g->rs;
}