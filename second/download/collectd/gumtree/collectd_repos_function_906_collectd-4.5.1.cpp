int plugin_register_log (char *name,
		void (*callback) (int priority, const char *msg))
{
	return (register_callback (&list_log, name, (void *) callback));
}