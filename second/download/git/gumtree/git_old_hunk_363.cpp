		mput_char(' ', longest - strlen(common_guides[i].name));
		puts(_(common_guides[i].help));
	}
	putchar('\n');
}

int cmd_help(int argc, const char **argv, const char *prefix)
{
	int nongit;
	char *alias;
	enum help_format parsed_help_format;

	argc = parse_options(argc, argv, prefix, builtin_help_options,
			builtin_help_usage, 0);
	parsed_help_format = help_format;

