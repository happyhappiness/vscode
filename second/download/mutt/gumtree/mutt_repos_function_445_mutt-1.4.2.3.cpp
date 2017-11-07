int hash_insert (HASH * table, const char *key, void *data, int allow_dup)
{
  struct hash_elem *ptr;
  int h;

  ptr = (struct hash_elem *) safe_malloc (sizeof (struct hash_elem));
  h = hash_string ((unsigned char *) key, table->nelem);
  ptr->key = key;
  ptr->data = data;

  if (allow_dup)
  {
    ptr->next = table->table[h];
    table->table[h] = ptr;
  }
  else
  {
    struct hash_elem *tmp, *last;
    int r;

    for (tmp = table->table[h], last = NULL; tmp; last = tmp, tmp = tmp->next)
    {
      r = mutt_strcmp (tmp->key, key);
      if (r == 0)
      {
	FREE (&ptr);
	return (-1);
      }
      if (r > 0)
	break;
    }
    if (last)
      last->next = ptr;
    else
      table->table[h] = ptr;
    ptr->next = tmp;
  }
  return h;
}