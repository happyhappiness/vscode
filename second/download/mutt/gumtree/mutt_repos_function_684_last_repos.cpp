int hash_insert (HASH * table, const char *strkey, void *data)
{
  union hash_key key;
  key.strkey = table->strdup_keys ? safe_strdup (strkey) : strkey;
  return union_hash_insert (table, key, data);
}