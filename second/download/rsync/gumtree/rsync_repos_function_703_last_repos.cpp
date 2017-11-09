int
main(int argc, char *argv[])
{
    int fd_file, len;
    struct timeval tv;
    fd_set fds;

    argv++;
    if (--argc && argv[0][0] == '-') {
	if (argv[0][1] == 'o')
	    save_data_from_program = 1;
	else if (argv[0][1] == 'i')
	    save_data_from_program = 0;
	else {
	    fprintf(stderr, "Unknown option: %s\n", argv[0]);
	    exit(1);
	}
	argv++;
	argc--;
    }
    if (argc < 2) {
	fprintf(stderr, "Usage: savetransfer [-i|-o] OUTPUT_FILE PROGRAM [ARGS...]\n");
	fprintf(stderr, "-i  Save the input going to PROGRAM to the OUTPUT_FILE\n");
	fprintf(stderr, "-o  Save the output coming from PROGRAM to the OUTPUT_FILE\n");
	exit(1);
    }
    if ((fd_file = open(*argv, O_WRONLY|O_TRUNC|O_CREAT|O_BINARY, 0644)) < 0) {
	fprintf(stderr, "Unable to write to `%s': %s\n", *argv, strerror(errno));
	exit(1);
    }
    set_blocking(fd_file);

    SIGACTION(SIGPIPE, SIG_IGN);

    run_program(argv + 1);

#if defined HAVE_SETMODE && O_BINARY
    setmode(STDIN_FILENO, O_BINARY);
    setmode(STDOUT_FILENO, O_BINARY);
#endif
    set_nonblocking(STDIN_FILENO);
    set_blocking(STDOUT_FILENO);

    while (1) {
	FD_ZERO(&fds);
	FD_SET(STDIN_FILENO, &fds);
	tv.tv_sec = TIMEOUT_SECONDS;
	tv.tv_usec = 0;
	if (!select(STDIN_FILENO+1, &fds, NULL, NULL, &tv))
	    break;
	if (!FD_ISSET(STDIN_FILENO, &fds))
	    break;
	if ((len = read(STDIN_FILENO, buf, sizeof buf)) <= 0)
	    break;
	if (write(STDOUT_FILENO, buf, len) != len) {
	    fprintf(stderr, "Failed to write data to stdout: %s\n", strerror(errno));
	    exit(1);
	}
	if (write(fd_file, buf, len) != len) {
	    fprintf(stderr, "Failed to write data to fd_file: %s\n", strerror(errno));
	    exit(1);
	}
    }
    return 0;
}