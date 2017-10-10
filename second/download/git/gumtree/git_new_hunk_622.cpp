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
