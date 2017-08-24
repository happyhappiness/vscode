{
	struct _7zip *zip;
	int r;
	size_t s;

	zip = (struct _7zip *)a->format_data;
	s = sizeof(zip->wbuff) - zip->wbuff_remaining;
	r = __archive_write_output(a, zip->wbuff, s);
	if (r != ARCHIVE_OK)
		return (r);
	zip->wbuff_remaining = sizeof(zip->wbuff);
	return (r);
}