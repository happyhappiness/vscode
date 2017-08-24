{
	struct v7tar *v7tar;
	int ret;

	v7tar = (struct v7tar *)a->format_data;
	if (s > v7tar->entry_bytes_remaining)
		s = (size_t)v7tar->entry_bytes_remaining;
	ret = __archive_write_output(a, buff, s);
	v7tar->entry_bytes_remaining -= s;
	if (ret != ARCHIVE_OK)
		return (ret);
	return (s);
}