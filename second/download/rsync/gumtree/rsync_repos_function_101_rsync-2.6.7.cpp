static void readfd(int fd, char *buffer, size_t N)
{
	int  cnt;
	size_t total = 0;

	while (total < N) {
		cnt = readfd_unbuffered(fd, buffer + total, N-total);
		total += cnt;
	}

	if (fd == write_batch_monitor_in) {
		if ((size_t)write(batch_fd, buffer, total) != total)
			exit_cleanup(RERR_FILEIO);
	}

	if (fd == sock_f_in)
		stats.total_read += total;
}