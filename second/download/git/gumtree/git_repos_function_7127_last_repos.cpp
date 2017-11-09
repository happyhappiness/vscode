static int keyring_erase(struct credential *c)
{
	GHashTable *attributes = NULL;
	GError *error = NULL;

	/*
	 * Sanity check that we actually have something to match
	 * against. The input we get is a restrictive pattern,
	 * so technically a blank credential means "erase everything".
	 * But it is too easy to accidentally send this, since it is equivalent
	 * to empty input. So explicitly disallow it, and require that the
	 * pattern have some actual content to match.
	 */
	if (!c->protocol && !c->host && !c->path && !c->username)
		return EXIT_FAILURE;

	attributes = make_attr_list(c);
	secret_password_clearv_sync(SECRET_SCHEMA_COMPAT_NETWORK,
				    attributes,
				    NULL,
				    &error);
	g_hash_table_unref(attributes);

	if (error != NULL) {
		g_critical("erase failed: %s", error->message);
		g_error_free(error);
		return EXIT_FAILURE;
	}

	return EXIT_SUCCESS;
}