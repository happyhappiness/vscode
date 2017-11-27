int strjoin (char *dst, size_t dst_len,
		char **fields, size_t fields_num,
		const char *sep)
{
	size_t field_len;
	size_t sep_len;
	int i;

	memset (dst, '\0', dst_len);

	if (fields_num <= 0)
		return (-1);

	sep_len = 0;
	if (sep != NULL)
		sep_len = strlen (sep);

	for (i = 0; i < (int)fields_num; i++)
	{
		if ((i > 0) && (sep_len > 0))
		{
			if (dst_len <= sep_len)
				return (-1);

			strncat (dst, sep, dst_len);
			dst_len -= sep_len;
		}

		field_len = strlen (fields[i]);

		if (dst_len <= field_len)
			return (-1);

		strncat (dst, fields[i], dst_len);
		dst_len -= field_len;
	}

	return (strlen (dst));
}