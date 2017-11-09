static void union_hash_delete (HASH *table, union hash_key key, const void *data,
		       void (*destroy) (void *))
{
  int hash;
  struct hash_elem *ptr, **last;

  if (!table)
    return;

  hash = table->gen_hash (key, table->nelem);
  ptr = table->table[hash];
  last = &table->table[hash];

  while (ptr)
  {
    if ((data == ptr->data || !data)
	&& table->cmp_key (ptr->key, key) == 0)
    {
      *last = ptr->next;
      if (destroy)
	destroy (ptr->data);
      if (table->strdup_keys)
        FREE (&ptr->key.strkey);
      FREE (&ptr);

      ptr = *last;
    }
    else
    {
      last = &ptr->next;
      ptr = ptr->next;
    }
  }
}