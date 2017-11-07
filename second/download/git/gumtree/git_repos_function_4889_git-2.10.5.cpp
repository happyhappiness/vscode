int cmd_remote_fd(int argc, const char **argv, const char *prefix)
{
	int input_fd = -1;
	int output_fd = -1;
	char *end;

	if (argc != 3)
		die("Expected two arguments");

	input_fd = (int)strtoul(argv[2], &end, 10);

	if ((end == argv[2]) || (*end != ',' && *end != '/' && *end))
		die("Bad URL syntax");

	if (*end == '/' || !*end) {
		output_fd = input_fd;
	} else {
		char *end2;
		output_fd = (int)strtoul(end + 1, &end2, 10);

		if ((end2 == end + 1) || (*end2 != '/' && *end2))
			die("Bad URL syntax");
	}

	command_loop(input_fd, output_fd);
	return 0;
}