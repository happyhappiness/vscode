static void readfd (int fd, char *buffer, size_t N)
{
	int  ret;
	size_t total=0;  
	
	while (total < N) {
		io_flush();

		ret = read_unbuffered (fd, buffer + total, N-total);
		total += ret;
	}

	stats.total_read += total;
}