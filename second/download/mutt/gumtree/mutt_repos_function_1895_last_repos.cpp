static int dup_hash_dec (HASH *dup_hash, char *s)
{
  struct hash_elem *elem;
  uintptr_t count;

  elem = hash_find_elem (dup_hash, s);
  if (!elem)
    return -1;

  count = (uintptr_t)elem->data;
  if (count <= 1)
  {
    hash_delete (dup_hash, s, NULL, NULL);
    return 0;
  }

  count--;
  elem->data = (void *)count;
  return count;
}