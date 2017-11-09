static void command_loop(int input_fd, int output_fd)
{
	char buffer[MAXCOMMAND];

	while (1) {
		size_t i;
		if (!fgets(buffer, MAXCOMMAND - 1, stdin)) {
			if (ferror(stdin))
				die("Input error");
			return;
		}
		/* Strip end of line characters. */
		i = strlen(buffer);
		while (i > 0 && isspace(buffer[i - 1]))
			buffer[--i] = 0;

		if (!strcmp(buffer, "capabilities")) {
			printf("*connect\n\n");
			fflush(stdout);
		} else if (!strncmp(buffer, "connect ", 8)) {
			printf("\n");
			fflush(stdout);
			if (bidirectional_transfer_loop(input_fd,
				output_fd))
				die("Copying data between file descriptors failed");
			return;
		} else {
			die("Bad command: %s", buffer);
		}
	}
}