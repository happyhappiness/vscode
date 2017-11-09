static int compare_objects(const unsigned char *buf, unsigned long size,
			   void *cb_data)
{
	struct compare_data *data = cb_data;

	if (data->buf_size < size) {
		free(data->buf);
		data->buf = xmalloc(size);
		data->buf_size = size;
	}

	while (size) {
		ssize_t len = read_istream(data->st, data->buf, size);
		if (len == 0)
			die(_("SHA1 COLLISION FOUND WITH %s !"),
			    oid_to_hex(&data->entry->idx.oid));
		if (len < 0)
			die(_("unable to read %s"),
			    oid_to_hex(&data->entry->idx.oid));
		if (memcmp(buf, data->buf, len))
			die(_("SHA1 COLLISION FOUND WITH %s !"),
			    oid_to_hex(&data->entry->idx.oid));
		size -= len;
		buf += len;
	}
	return 0;
}