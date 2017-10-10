		fclose(in);
		fclose(out);
	}
	return 1;
}

static void serve_cache(const char *socket_path)
{
	int fd;

	fd = unix_stream_listen(socket_path);
	if (fd < 0)
		die_errno("unable to bind to '%s'", socket_path);

	printf("ok\n");
	fclose(stdout);

	while (serve_cache_loop(fd))
		; /* nothing */

	close(fd);
	unlink(socket_path);
