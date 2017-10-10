	sigchain_push_common(remove_pidfile_on_signal);
	atexit(remove_pidfile);

	return NULL;
}

int cmd_gc(int argc, const char **argv, const char *prefix)
{
	int aggressive = 0;
	int auto_gc = 0;
	int quiet = 0;
	int force = 0;
