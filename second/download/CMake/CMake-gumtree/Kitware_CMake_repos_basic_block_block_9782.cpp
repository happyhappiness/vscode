{
	int new_fd;
#ifdef F_DUPFD_CLOEXEC
	static volatile int can_dupfd_cloexec = 1;

	if (can_dupfd_cloexec) {
		new_fd = fcntl(fd, F_DUPFD_CLOEXEC, 0);
		if (new_fd != -1)
			return (new_fd);
		/* Linux 2.6.18 - 2.6.23 declare F_DUPFD_CLOEXEC,
		 * but it cannot be used. So we have to try dup(). */
		/* We won't try F_DUPFD_CLOEXEC. */
		can_dupfd_cloexec = 0;
	}
#endif /* F_DUPFD_CLOEXEC */
	new_fd = dup(fd);
	__archive_ensure_cloexec_flag(new_fd);
	return (new_fd);
}