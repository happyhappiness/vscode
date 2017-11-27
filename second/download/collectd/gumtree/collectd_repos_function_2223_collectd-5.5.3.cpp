int strjoin (char *buffer, size_t buffer_size,
		char **fields, size_t fields_num,
		const char *sep)
{
	size_t avail;
	char *ptr;
	size_t sep_len;
	size_t i;

	if ((buffer_size < 1) || (fields_num <= 0))
		return (-1);

	memset (buffer, 0, buffer_size);
	ptr = buffer;
	avail = buffer_size - 1;

	sep_len = 0;
	if (sep != NULL)
		sep_len = strlen (sep);

	for (i = 0; i < fields_num; i++)
	{
		size_t field_len;

		if ((i > 0) && (sep_len > 0))
		{
			if (avail < sep_len)
				return (-1);

			memcpy (ptr, sep, sep_len);
			ptr += sep_len;
			avail -= sep_len;
		}

		field_len = strlen (fields[i]);
		if (avail < field_len)
			return (-1);

		memcpy (ptr, fields[i], field_len);
		ptr += field_len;
		avail -= field_len;
	}

	assert (buffer[buffer_size - 1] == 0);
	return (strlen (buffer));
}