	{ "git-upload-pack", do_generic_cmd },
	{ "git-upload-archive", do_generic_cmd },
	{ "cvs", do_cvs_cmd },
	{ NULL },
};

int cmd_main(int argc, const char **argv)
{
	char *prog;
	const char **user_argv;
	struct commands *cmd;
	int count;

	/*
	 * Special hack to pretend to be a CVS server
	 */
	if (argc == 2 && !strcmp(argv[1], "cvs server")) {
		argv--;
	} else if (argc == 1) {
