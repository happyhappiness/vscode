static size_t fwrite_sha1_file(char *ptr, size_t eltsize, size_t nmemb,
			       void *data)
{
	unsigned char expn[4096];
	size_t size = eltsize * nmemb;
	int posn = 0;
	struct http_object_request *freq = data;
	struct active_request_slot *slot = freq->slot;

	if (slot) {
		CURLcode c = curl_easy_getinfo(slot->curl, CURLINFO_HTTP_CODE,
						&slot->http_code);
		if (c != CURLE_OK)
			die("BUG: curl_easy_getinfo for HTTP code failed: %s",
				curl_easy_strerror(c));
		if (slot->http_code >= 300)
			return size;
	}

	do {
		ssize_t retval = xwrite(freq->localfile,
					(char *) ptr + posn, size - posn);
		if (retval < 0)
			return posn;
		posn += retval;
	} while (posn < size);

	freq->stream.avail_in = size;
	freq->stream.next_in = (void *)ptr;
	do {
		freq->stream.next_out = expn;
		freq->stream.avail_out = sizeof(expn);
		freq->zret = git_inflate(&freq->stream, Z_SYNC_FLUSH);
		git_SHA1_Update(&freq->c, expn,
				sizeof(expn) - freq->stream.avail_out);
	} while (freq->stream.avail_in && freq->zret == Z_OK);
	return size;
}