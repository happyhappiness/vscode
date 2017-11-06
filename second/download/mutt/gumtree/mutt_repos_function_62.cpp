static void dump_menu (FILE *f, int menu)
{
  struct keymap_t *map;
  const struct binding_t *b;
  char buf[SHORT_STRING];

  /* browse through the keymap table */
  for (map = Keymaps[menu]; map; map = map->next)
  {
    if (map->op != OP_NULL)
    {
      km_expand_key (buf, sizeof (buf), map);

      if (map->op == OP_MACRO)
      {
	if (map->descr == NULL)
	  format_line (f, -1, buf, "macro", map->macro);
        else
	  format_line (f, 1, buf, map->macro, map->descr);
      }
      else
      {
	b = help_lookupFunction (map->op, menu);
	format_line (f, 0, buf, b ? b->name : "UNKNOWN",
	      b ? _(HelpStrings[b->op]) : _("ERROR: please report this bug"));
      }
    }
  }
}