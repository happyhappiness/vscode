static void remove_credential(const char *fn, struct credential *c)
{
	/*
	 * Sanity check that we actually have something to match
	 * against. The input we get is a restrictive pattern,
	 * so technically a blank credential means "erase everything".
	 * But it is too easy to accidentally send this, since it is equivalent
	 * to empty input. So explicitly disallow it, and require that the
	 * pattern have some actual content to match.
	 */
	if (c->protocol || c->host || c->path || c->username)
		rewrite_credential_file(fn, c, NULL);
}