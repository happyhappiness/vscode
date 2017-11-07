static void dump_unbound (FILE *f,
			  const struct binding_t *funcs,
			  struct keymap_t *map,
			  struct keymap_t *aux)
{
  int i;

  for (i = 0; funcs[i].name; i++)
  {
    if (! is_bound (map, funcs[i].op) &&
	(!aux || ! is_bound (aux, funcs[i].op)))
      format_line (f, 0, funcs[i].name, "", _(HelpStrings[funcs[i].op]));
  }
}