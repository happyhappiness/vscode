{
	if (write_in_full(fd, buf, count) < 0) {
		check_pipe(errno);
		die_errno("write error");
	}
}
