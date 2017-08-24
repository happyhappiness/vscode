{
	struct archive_write_disk *a = (struct archive_write_disk *)_a;
	(void)n; /* UNUSED */
	if (n == -1 || n == 0)
		return (a->total_bytes_written);
	return (-1);
}