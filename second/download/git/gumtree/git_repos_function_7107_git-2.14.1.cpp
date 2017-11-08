static int keyring_store(struct credential *c)
{
	char *label = NULL;
	GHashTable *attributes = NULL;
	GError *error = NULL;

	/*
	 * Sanity check that what we are storing is actually sensible.
	 * In particular, we can't make a URL without a protocol field.
	 * Without either a host or pathname (depending on the scheme),
	 * we have no primary key. And without a username and password,
	 * we are not actually storing a credential.
	 */
	if (!c->protocol || !(c->host || c->path) ||
	    !c->username || !c->password)
		return EXIT_FAILURE;

	label = make_label(c);
	attributes = make_attr_list(c);
	secret_password_storev_sync(SECRET_SCHEMA_COMPAT_NETWORK,
				    attributes,
				    NULL,
				    label,
				    c->password,
				    NULL,
				    &error);
	g_free(label);
	g_hash_table_unref(attributes);

	if (error != NULL) {
		g_critical("store failed: %s", error->message);
		g_error_free(error);
		return EXIT_FAILURE;
	}

	return EXIT_SUCCESS;
}