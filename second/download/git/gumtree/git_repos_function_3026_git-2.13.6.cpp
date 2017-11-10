static int has_cr_in_index(const char *path)
{
	unsigned long sz;
	void *data;
	int has_cr;

	data = read_blob_data_from_cache(path, &sz);
	if (!data)
		return 0;
	has_cr = memchr(data, '\r', sz) != NULL;
	free(data);
	return has_cr;
}