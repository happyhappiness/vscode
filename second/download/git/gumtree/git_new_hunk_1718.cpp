	return NULL;
}

static int check_emacsclient_version(void)
{
	struct strbuf buffer = STRBUF_INIT;
	struct child_process ec_process = CHILD_PROCESS_INIT;
	const char *argv_ec[] = { "emacsclient", "--version", NULL };
	int version;

	/* emacsclient prints its version number on stderr */
	ec_process.argv = argv_ec;
	ec_process.err = -1;
	ec_process.stdout_to_stderr = 1;
	if (start_command(&ec_process))
		return error(_("Failed to start emacsclient."));

