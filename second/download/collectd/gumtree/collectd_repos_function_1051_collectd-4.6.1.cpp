int plugin_register_flush (const char *name,
		int (*callback) (const int timeout, const char *identifier))
{
	return (register_callback (&list_flush, name, (void *) callback));
}