static size_t fwrite_sha1_file(char *ptr, size_t eltsize, size_t nmemb,
			       void *data)
{
	unsigned char expn[4096];
	size_t size = eltsize * nmemb;
	int posn = 0;
	struct http_object_request *freq =
		(struct http_object_request *)data;
	do {
		ssize_t retval = xwrite(freq->localfile,
					(char *) ptr + posn, size - posn);
		if (retval < 0)
			return posn;
		posn += retval;
