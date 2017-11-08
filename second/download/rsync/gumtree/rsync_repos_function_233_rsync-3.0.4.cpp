void close_all(void)
{
#ifdef SHUTDOWN_ALL_SOCKETS
	int max_fd;
	int fd;
	int ret;
	STRUCT_STAT st;

	max_fd = sysconf(_SC_OPEN_MAX) - 1;
	for (fd = max_fd; fd >= 0; fd--) {
		if ((ret = do_fstat(fd, &st)) == 0) {
			if (is_a_socket(fd))
				ret = shutdown(fd, 2);
			ret = close(fd);
		}
	}
#endif
}