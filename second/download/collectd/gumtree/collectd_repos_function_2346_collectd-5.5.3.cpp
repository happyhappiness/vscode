void cf_register (const char *type,
		int (*callback) (const char *, const char *),
		const char **keys, int keys_num)
{
	cf_callback_t *cf_cb;

	/* Remove this module from the list, if it already exists */
	cf_unregister (type);

	/* This pointer will be free'd in `cf_unregister' */
	if ((cf_cb = (cf_callback_t *) malloc (sizeof (cf_callback_t))) == NULL)
		return;

	cf_cb->type     = type;
	cf_cb->callback = callback;
	cf_cb->keys     = keys;
	cf_cb->keys_num = keys_num;
	cf_cb->ctx      = plugin_get_ctx ();

	cf_cb->next = first_callback;
	first_callback = cf_cb;
}