struct keymap_t *km_find_func (int menu, int func)
{
  struct keymap_t *map = Keymaps[menu];

  for (; map; map = map->next)
    if (map->op == func)
      break;
  return (map);
}