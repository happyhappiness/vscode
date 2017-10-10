		mput_char(' ', longest - strlen(common_guides[i].name));
		puts(_(common_guides[i].help));
	}
	putchar('\n');
}

static const char *check_git_cmd(const char* cmd)
{
	char *alias;

	if (is_git_command(cmd))
		return cmd;

	alias = alias_lookup(cmd);
	if (alias) {
		printf_ln(_("`git %s' is aliased to `%s'"), cmd, alias);
		free(alias);
		exit(0);
	}

	if (exclude_guides)
		return help_unknown_cmd(cmd);

	return cmd;
}

int cmd_help(int argc, const char **argv, const char *prefix)
{
	int nongit;
	enum help_format parsed_help_format;

	argc = parse_options(argc, argv, prefix, builtin_help_options,
			builtin_help_usage, 0);
	parsed_help_format = help_format;

