void km_bind (char *s, int menu, int op, char *macro, char *descr)
{
  struct keymap_t *map, *tmp, *last = NULL, *next;
  keycode_t buf[MAX_SEQ];
  int len, pos = 0, lastpos = 0;

  len = parsekeys (s, buf, MAX_SEQ);

  map = allocKeys (len, buf);
  map->op = op;
  map->macro = safe_strdup (macro);
  map->descr = safe_strdup (descr);

  tmp = Keymaps[menu];

  while (tmp)
  {
    if (pos >= len || pos >= tmp->len)
    {
      /* map and tmp match, but have different lengths, so overwrite */
      do
      {
	len = tmp->eq;
	next = tmp->next;
	FREE (&tmp->macro);
	FREE (&tmp->keys);
	FREE (&tmp->descr);
	FREE (&tmp);
	tmp = next;
      }
      while (tmp && len >= pos);
      map->eq = len;
      break;
    }
    else if (buf[pos] == tmp->keys[pos])
      pos++;
    else if (buf[pos] < tmp->keys[pos])
    {
      /* found location to insert between last and tmp */
      map->eq = pos;
      break;
    }
    else /* buf[pos] > tmp->keys[pos] */
    {
      last = tmp;
      lastpos = pos;
      if (pos > tmp->eq)
	pos = tmp->eq;
      tmp = tmp->next;
    }
  }

  map->next = tmp;
  if (last)
  {
    last->next = map;
    last->eq = lastpos;
  }
  else
    Keymaps[menu] = map;
}