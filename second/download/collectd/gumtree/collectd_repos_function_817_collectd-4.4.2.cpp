int plugin_register_flush (const char *name, int (*callback) (const int))
{
	return (register_callback (&list_flush, name, (void *) callback));
}