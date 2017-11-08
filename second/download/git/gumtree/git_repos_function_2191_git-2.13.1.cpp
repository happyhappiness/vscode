static int attr_hash_entry_cmp(const struct attr_hash_entry *a,
			       const struct attr_hash_entry *b,
			       void *unused)
{
	return (a->keylen != b->keylen) || strncmp(a->key, b->key, a->keylen);
}