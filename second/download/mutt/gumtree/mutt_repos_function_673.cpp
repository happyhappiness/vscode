void hash_delete_hash (HASH * table, int hash, const char *key, const void *data,
		       void (*destroy) (void *))
{
  struct hash_elem *ptr = table->table[hash];
  struct hash_elem **last = &table->table[hash];

  while (ptr) 
  {
    if ((data == ptr->data || !data)
	&& table->cmp_string (ptr->key, key) == 0)
    {
      *last = ptr->next;
      if (destroy)
	destroy (ptr->data);
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