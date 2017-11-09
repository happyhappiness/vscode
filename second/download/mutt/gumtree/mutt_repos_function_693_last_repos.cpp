void hash_delete (HASH *table, const char *strkey, const void *data,
                  void (*destroy) (void *))
{
  union hash_key key;
  key.strkey = strkey;
  union_hash_delete (table, key, data, destroy);
}