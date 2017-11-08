int full_write(int desc, const char *ptr, size_t len)
{
	int total_written;

	total_written = 0;
	while (len > 0) {
		int written = write(desc, ptr, len);
		if (written < 0)  {
			if (errno == EINTR)
				continue;
			return written;
		}
		total_written += written;
		ptr += written;
		len -= written;
	}
	return total_written;
}