static int value_list_to_filename (char *buffer, size_t buffer_size,
		value_list_t const *vl)
{
	char const suffix[] = ".rrd";
	int status;
	size_t len;

	if (datadir != NULL)
	{
		size_t datadir_len = strlen (datadir) + 1;

		if (datadir_len >= buffer_size)
			return (ENOMEM);

		sstrncpy (buffer, datadir, buffer_size);
		buffer[datadir_len - 1] = '/';
		buffer[datadir_len] = 0;

		buffer += datadir_len;
		buffer_size -= datadir_len;
	}

	status = FORMAT_VL (buffer, buffer_size, vl);
	if (status != 0)
		return (status);

	len = strlen (buffer);
	assert (len < buffer_size);
	buffer += len;
	buffer_size -= len;

	if (buffer_size <= sizeof (suffix))
		return (ENOMEM);

	memcpy (buffer, suffix, sizeof (suffix));
	return (0);
}