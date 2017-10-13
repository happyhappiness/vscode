static void serve_cache(const char *socket_path, int debug)
{
	int fd;

	fd = unix_stream_listen(socket_path);
	if (fd < 0)
		die_errno("unable to bind to '%s'", socket_path);

	printf("ok\n");
	fclose(stdout);
	if (!debug) {
		if (!freopen("/dev/null", "w", stderr))
			die_errno("unable to point stderr to /dev/null");
	}

	while (serve_cache_loop(fd))
		; /* nothing */

	close(fd);
	unlink(socket_path);
}