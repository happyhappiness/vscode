char *url_decode(const char *url)
{
	return url_decode_mem(url, strlen(url));
}