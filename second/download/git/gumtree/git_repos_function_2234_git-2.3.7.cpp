static void remove_credential(const struct credential *c)
{
	struct credential_cache_entry *e;

	e = lookup_credential(c);
	if (e)
		e->expiration = 0;
}