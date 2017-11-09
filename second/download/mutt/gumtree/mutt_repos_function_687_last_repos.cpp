static void *union_hash_find (const HASH *table, union hash_key key)
{
  struct hash_elem *ptr = union_hash_find_elem (table, key);
  if (ptr)
    return ptr->data;
  else
    return NULL;
}