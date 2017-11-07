static void parse_option(void)
{
	char *option = command_buf.buf + 11;

	if (seen_data_command)
		die("Got option command '%s' after data command", option);

	if (parse_one_option(option))
		return;

	die("This version of fast-import does not support option: %s", option);
}