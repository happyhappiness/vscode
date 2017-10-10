		return 0;
	}

	return 1;
}

static void parse_feature(const char *feature)
{
	if (seen_data_command)
		die("Got feature command '%s' after data command", feature);

	if (parse_one_feature(feature, 1))
		return;

	die("This version of fast-import does not support feature %s.", feature);
}

static void parse_option(const char *option)
{
	if (seen_data_command)
		die("Got option command '%s' after data command", option);

	if (parse_one_option(option))
		return;

