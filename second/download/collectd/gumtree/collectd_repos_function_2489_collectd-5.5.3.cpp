plugin_ctx_t plugin_set_ctx (plugin_ctx_t ctx)
{
	plugin_ctx_t *c;
	plugin_ctx_t old;

	assert (plugin_ctx_key_initialized);
	c = pthread_getspecific (plugin_ctx_key);

	if (c == NULL) {
		c = plugin_ctx_create ();
		/* this must no happen -- exit() instead? */
		if (c == NULL)
			return ctx_init;
	}

	old = *c;
	*c = ctx;

	return (old);
}