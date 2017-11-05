int cmd_submodule__helper(int argc, const char **argv, const char *prefix)
{
	int i;
	if (argc < 2)
		die(_("submodule--helper subcommand must be "
		      "called with a subcommand"));

	for (i = 0; i < ARRAY_SIZE(commands); i++) {
		if (!strcmp(argv[1], commands[i].cmd)) {
			if (get_super_prefix() &&
			    !(commands[i].option & SUPPORT_SUPER_PREFIX))
				die(_("%s doesn't support --super-prefix"),
				    commands[i].cmd);
			return commands[i].fn(argc - 1, argv + 1, prefix);
		}
	}

	die(_("'%s' is not a valid submodule--helper "
	      "subcommand"), argv[1]);
}