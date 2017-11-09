static int attr_hash_entry_cmp(void *unused_cmp_data,
			       const struct attr_hash_entry *a,
			       const struct attr_hash_entry *b,
			       void *unused_keydata)
{
	return (a->keylen != b->keylen) || strncmp(a->key, b->key, a->keylen);
}