
	printf("%s", ret);
	strbuf_release(&sb);
	return 0;
}

struct cmd_struct {
	const char *cmd;
	int (*fn)(int, const char **, const char *);
};

static struct cmd_struct commands[] = {
	{"list", module_list},
	{"name", module_name},
	{"clone", module_clone},
	{"update-clone", update_clone},
	{"relative-path", resolve_relative_path},
	{"resolve-relative-url", resolve_relative_url},
	{"resolve-relative-url-test", resolve_relative_url_test},
	{"init", module_init},
	{"remote-branch", resolve_remote_submodule_branch}
};

int cmd_submodule__helper(int argc, const char **argv, const char *prefix)
{
	int i;
	if (argc < 2)
		die(_("submodule--helper subcommand must be "
		      "called with a subcommand"));

	for (i = 0; i < ARRAY_SIZE(commands); i++)
		if (!strcmp(argv[1], commands[i].cmd))
			return commands[i].fn(argc - 1, argv + 1, prefix);

	die(_("'%s' is not a valid submodule--helper "
	      "subcommand"), argv[1]);
}
