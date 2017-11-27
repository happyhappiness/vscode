plugin_ctx_t plugin_get_ctx (void)
{
	plugin_ctx_t *ctx;

	assert (plugin_ctx_key_initialized);
	ctx = pthread_getspecific (plugin_ctx_key);

	if (ctx == NULL) {
		ctx = plugin_ctx_create ();
		/* this must no happen -- exit() instead? */
		if (ctx == NULL)
			return ctx_init;
	}

	return (*ctx);
}