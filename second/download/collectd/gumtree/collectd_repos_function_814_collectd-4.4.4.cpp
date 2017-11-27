int plugin_register_init (const char *name,
		int (*callback) (void))
{
	return (register_callback (&list_init, name, (void *) callback));
}