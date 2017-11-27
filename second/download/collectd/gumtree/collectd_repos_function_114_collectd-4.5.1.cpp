static size_t apache_curl_callback (void *buf, size_t size, size_t nmemb,
		void *stream)
{
	size_t len = size * nmemb;

	if (len <= 0)
		return (len);

	if ((apache_buffer_fill + len) >= apache_buffer_size)
	{
		char *temp;

		temp = (char *) realloc (apache_buffer,
				apache_buffer_fill + len + 1);
		if (temp == NULL)
		{
			ERROR ("apache plugin: realloc failed.");
			return (0);
		}
		apache_buffer = temp;
		apache_buffer_size = apache_buffer_fill + len + 1;
	}

	memcpy (apache_buffer + apache_buffer_fill, (char *) buf, len);
	apache_buffer_fill += len;
	apache_buffer[apache_buffer_fill] = 0;

	return (len);
}