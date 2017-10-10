{
	remove_pidfile();
	sigchain_pop(signo);
	raise(signo);
}

static void gc_config(void)
{
	const char *value;

	if (!git_config_get_value("gc.packrefs", &value)) {
		if (value && !strcmp(value, "notbare"))
