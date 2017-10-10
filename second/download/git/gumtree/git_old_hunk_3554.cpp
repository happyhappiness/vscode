	{ "git-upload-pack", do_generic_cmd },
	{ "git-upload-archive", do_generic_cmd },
	{ "cvs", do_cvs_cmd },
	{ NULL },
};

int main(int argc, char **argv)
{
	char *prog;
	const char **user_argv;
	struct commands *cmd;
	int count;

	git_setup_gettext();

	git_extract_argv0_path(argv[0]);

	/*
	 * Always open file descriptors 0/1/2 to avoid clobbering files
	 * in die().  It also avoids messing up when the pipes are dup'ed
	 * onto stdin/stdout/stderr in the child processes we spawn.
	 */
	sanitize_stdfds();

	/*
	 * Special hack to pretend to be a CVS server
	 */
	if (argc == 2 && !strcmp(argv[1], "cvs server")) {
		argv--;
	} else if (argc == 1) {
