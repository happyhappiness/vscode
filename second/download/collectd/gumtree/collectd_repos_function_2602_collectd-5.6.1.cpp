static int plugin_flush_timeout_callback (user_data_t *ud)
{
	flush_callback_t *cb = ud->data;

	return plugin_flush (cb->name, cb->timeout, /* identifier = */ NULL);
}