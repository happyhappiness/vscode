static void create_bindings (const struct binding_t *map, int menu)
{
  int i;

  for (i = 0 ; map[i].name ; i++)
    if (map[i].seq)
      km_bindkey (map[i].seq, menu, map[i].op);
}