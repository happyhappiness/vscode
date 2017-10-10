		return 0;
	}

	return 1;
}

static void parse_feature(void)
{
	char *feature = command_buf.buf + 8;

	if (seen_data_command)
		die("Got feature command '%s' after data command", feature);

	if (parse_one_feature(feature, 1))
		return;

	die("This version of fast-import does not support feature %s.", feature);
}

static void parse_option(void)
{
	char *option = command_buf.buf + 11;

	if (seen_data_command)
		die("Got option command '%s' after data command", option);

	if (parse_one_option(option))
		return;

