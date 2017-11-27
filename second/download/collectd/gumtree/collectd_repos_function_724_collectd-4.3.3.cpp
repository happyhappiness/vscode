int plugin_register_shutdown (char *name,
		int (*callback) (void))
{
	return (register_callback (&list_shutdown, name, (void *) callback));
}