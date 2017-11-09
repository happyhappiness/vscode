static const struct binding_t *help_lookupFunction (int op, int menu)
{
  int i;
  const struct binding_t *map;

  if (menu != MENU_PAGER)
  {
    /* first look in the generic map for the function */
    for (i = 0; OpGeneric[i].name; i++)
      if (OpGeneric[i].op == op)
	return (&OpGeneric[i]);    
  }

  if ((map = km_get_table(menu)))
  {
    for (i = 0; map[i].name; i++)
      if (map[i].op == op)
	return (&map[i]);
  }
  
  return (NULL);
}