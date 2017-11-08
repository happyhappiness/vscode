static void readfd(int fd, char *buffer, size_t N)
{
	int  ret;
	size_t total = 0;

	while (total < N) {
		ret = readfd_unbuffered(fd, buffer + total, N-total);
		total += ret;
	}

	if (fd == write_batch_monitor_in) {
		if ((size_t)write(batch_fd, buffer, total) != total)
			exit_cleanup(RERR_FILEIO);
	}

	if (fd == sock_f_in)
		stats.total_read += total;
}