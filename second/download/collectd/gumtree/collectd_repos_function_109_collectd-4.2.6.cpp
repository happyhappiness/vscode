static size_t apache_curl_callback (void *buf, size_t size, size_t nmemb, void *stream)
{
	size_t len = size * nmemb;

	if ((apache_buffer_len + len) >= ABUFFER_SIZE)
	{
		len = (ABUFFER_SIZE - 1) - apache_buffer_len;
	}

	if (len <= 0)
		return (len);

	memcpy (apache_buffer + apache_buffer_len, (char *) buf, len);
	apache_buffer_len += len;
	apache_buffer[apache_buffer_len] = '\0';

	return (len);
}