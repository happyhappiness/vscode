static struct credential_cache_entry *lookup_credential(const struct credential *c)
{
	int i;
	for (i = 0; i < entries_nr; i++) {
		struct credential *e = &entries[i].item;
		if (credential_match(c, e))
			return &entries[i];
	}
	return NULL;
}