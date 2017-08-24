{
	struct ustar *ustar;
	int ret;

	ustar = (struct ustar *)a->format_data;
	if (s > ustar->entry_bytes_remaining)
		s = (size_t)ustar->entry_bytes_remaining;
	ret = __archive_write_output(a, buff, s);
	ustar->entry_bytes_remaining -= s;
	if (ret != ARCHIVE_OK)
		return (ret);
	return (s);
}