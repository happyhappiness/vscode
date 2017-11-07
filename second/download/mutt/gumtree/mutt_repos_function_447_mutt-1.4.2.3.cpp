void hash_delete_hash (HASH * table, int hash, const char *key, const void *data,
		       void (*destroy) (void *))
{
  struct hash_elem *ptr = table->table[hash];
  struct hash_elem **last = &table->table[hash];

  for (; ptr; last = &ptr->next, ptr = ptr->next)
  {
    /* if `data' is given, look for a matching ->data member.  this is
     * required for the case where we have multiple entries with the same
     * key
     */
    if ((data == ptr->data) || (!data && mutt_strcmp (ptr->key, key) == 0))
    {
      *last = ptr->next;
      if (destroy) destroy (ptr->data);
      FREE (&ptr);
      return;
    }
  }
}