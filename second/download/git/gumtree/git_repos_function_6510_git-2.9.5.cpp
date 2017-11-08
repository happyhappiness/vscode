static int keyring_store(struct credential *c)
{
	guint32 item_id;
	char *object = NULL;
	GnomeKeyringResult result;

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

	object = keyring_object(c);

	result = gnome_keyring_set_network_password_sync(
				GNOME_KEYRING_DEFAULT,
				c->username,
				NULL /* domain */,
				c->host,
				object,
				c->protocol,
				NULL /* authtype */,
				c->port,
				c->password,
				&item_id);

	g_free(object);

	if (result != GNOME_KEYRING_RESULT_OK &&
	    result != GNOME_KEYRING_RESULT_CANCELLED) {
		g_critical("%s", gnome_keyring_result_to_message(result));
		return EXIT_FAILURE;
	}

	return EXIT_SUCCESS;
}