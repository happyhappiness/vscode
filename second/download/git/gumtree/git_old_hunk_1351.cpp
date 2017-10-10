{
	int input_fd = -1;
	int output_fd = -1;
	char *end;

	if (argc != 3)
		die("Expected two arguments");

	input_fd = (int)strtoul(argv[2], &end, 10);

	if ((end == argv[2]) || (*end != ',' && *end != '/' && *end))
		die("Bad URL syntax");

