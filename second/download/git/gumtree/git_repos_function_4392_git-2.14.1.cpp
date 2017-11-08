static int remotes_hash_cmp(const void *unused_cmp_data,
			    const struct remote *a,
			    const struct remote *b,
			    const struct remotes_hash_key *key)
{
	if (key)
		return strncmp(a->name, key->str, key->len) || a->name[key->len];
	else
		return strcmp(a->name, b->name);
}