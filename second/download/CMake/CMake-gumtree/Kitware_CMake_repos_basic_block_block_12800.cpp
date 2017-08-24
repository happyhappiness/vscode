{
	int err;

	err = read_body_to_string(a, tar, &(tar->pax_global), h, unconsumed);
	if (err != ARCHIVE_OK)
		return (err);
	err = tar_read_header(a, tar, entry, unconsumed);
	return (err);
}