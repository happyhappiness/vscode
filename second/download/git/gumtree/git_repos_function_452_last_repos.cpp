static void store_credential(const struct string_list *fns, struct credential *c)
{
	struct string_list_item *fn;

	/*
	 * Sanity check that what we are storing is actually sensible.
	 * In particular, we can't make a URL without a protocol field.
	 * Without either a host or pathname (depending on the scheme),
	 * we have no primary key. And without a username and password,
	 * we are not actually storing a credential.
	 */
	if (!c->protocol || !(c->host || c->path) || !c->username || !c->password)
		return;

	for_each_string_list_item(fn, fns)
		if (!access(fn->string, F_OK)) {
			store_credential_file(fn->string, c);
			return;
		}
	/*
	 * Write credential to the filename specified by fns->items[0], thus
	 * creating it
	 */
	if (fns->nr)
		store_credential_file(fns->items[0].string, c);
}