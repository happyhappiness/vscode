const char *get_cached_convert_stats_ascii(const struct index_state *istate,
					   const char *path)
{
	const char *ret;
	unsigned long sz;
	void *data = read_blob_data_from_index(istate, path, &sz);
	ret = gather_convert_stats_ascii(data, sz);
	free(data);
	return ret;
}