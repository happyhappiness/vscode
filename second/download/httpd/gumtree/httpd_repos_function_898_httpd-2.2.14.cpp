void cache_hash_this(cache_hash_index_t *hi,
                                  const void **key,
                                  apr_ssize_t *klen,
                                  void **val)
{
    if (key)  *key  = hi->this->key;
    if (klen) *klen = hi->this->klen;
    if (val)  *val  = (void *)hi->this->val;
}