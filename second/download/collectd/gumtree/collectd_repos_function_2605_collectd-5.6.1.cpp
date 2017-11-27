int plugin_register_flush (const char *name,
		plugin_flush_cb callback, user_data_t const *ud)
{
	int status;
	plugin_ctx_t ctx = plugin_get_ctx ();

	status = create_register_callback (&list_flush, name,
		(void *) callback, ud);
	if (status != 0)
		return status;

	if (ctx.flush_interval != 0)
	{
		char *flush_name;
		flush_callback_t *cb;

		flush_name = plugin_flush_callback_name (name);
		if (flush_name == NULL)
			return (-1);

		cb = malloc(sizeof (*cb));
		if (cb == NULL)
		{
			ERROR ("plugin_register_flush: malloc failed.");
			sfree (flush_name);
			return (-1);
		}

		cb->name = strdup (name);
		if (cb->name == NULL)
		{
			ERROR ("plugin_register_flush: strdup failed.");
			sfree (cb);
			sfree (flush_name);
			return (-1);
		}
		cb->timeout = ctx.flush_timeout;

		status = plugin_register_complex_read (
			/* group     = */ "flush",
			/* name      = */ flush_name,
			/* callback  = */ plugin_flush_timeout_callback,
			/* interval  = */ ctx.flush_interval,
			/* user data = */ &(user_data_t) {
				.data = cb,
				.free_func = plugin_flush_timeout_callback_free,
			});

		sfree (flush_name);
		if (status != 0)
		{
			sfree (cb->name);
			sfree (cb);
			return status;
		}
	}

	return 0;
}