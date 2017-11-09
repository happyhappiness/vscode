static int keyring_get(struct credential *c)
{
	SecretService *service = NULL;
	GHashTable *attributes = NULL;
	GError *error = NULL;
	GList *items = NULL;

	if (!c->protocol || !(c->host || c->path))
		return EXIT_FAILURE;

	service = secret_service_get_sync(0, NULL, &error);
	if (error != NULL) {
		g_critical("could not connect to Secret Service: %s", error->message);
		g_error_free(error);
		return EXIT_FAILURE;
	}

	attributes = make_attr_list(c);
	items = secret_service_search_sync(service,
					   SECRET_SCHEMA_COMPAT_NETWORK,
					   attributes,
					   SECRET_SEARCH_LOAD_SECRETS,
					   NULL,
					   &error);
	g_hash_table_unref(attributes);
	if (error != NULL) {
		g_critical("lookup failed: %s", error->message);
		g_error_free(error);
		return EXIT_FAILURE;
	}

	if (items != NULL) {
		SecretItem *item;
		SecretValue *secret;
		const char *s;

		item = items->data;
		secret = secret_item_get_secret(item);
		attributes = secret_item_get_attributes(item);

		s = g_hash_table_lookup(attributes, "user");
		if (s) {
			g_free(c->username);
			c->username = g_strdup(s);
		}

		s = secret_value_get_text(secret);
		if (s) {
			g_free(c->password);
			c->password = g_strdup(s);
		}

		g_hash_table_unref(attributes);
		secret_value_unref(secret);
		g_list_free_full(items, g_object_unref);
	}

	return EXIT_SUCCESS;
}