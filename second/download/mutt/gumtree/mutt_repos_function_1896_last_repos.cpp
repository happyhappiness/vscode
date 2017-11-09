static int dup_hash_inc (HASH *dup_hash, char *s)
{
  struct hash_elem *elem;
  uintptr_t count;

  elem = hash_find_elem (dup_hash, s);
  if (!elem)
  {
    count = 1;
    hash_insert (dup_hash, s, (void *)count);
    return count;
  }

  count = (uintptr_t)elem->data;
  count++;
  elem->data = (void *)count;
  return count;
}