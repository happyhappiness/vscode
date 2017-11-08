int finish_http_object_request(struct http_object_request *freq)
{
	struct stat st;

	close(freq->localfile);
	freq->localfile = -1;

	process_http_object_request(freq);

	if (freq->http_code == 416) {
		warning("requested range invalid; we may already have all the data.");
	} else if (freq->curl_result != CURLE_OK) {
		if (stat(freq->tmpfile, &st) == 0)
			if (st.st_size == 0)
				unlink_or_warn(freq->tmpfile);
		return -1;
	}

	git_inflate_end(&freq->stream);
	git_SHA1_Final(freq->real_sha1, &freq->c);
	if (freq->zret != Z_STREAM_END) {
		unlink_or_warn(freq->tmpfile);
		return -1;
	}
	if (hashcmp(freq->sha1, freq->real_sha1)) {
		unlink_or_warn(freq->tmpfile);
		return -1;
	}
	freq->rename =
		move_temp_to_file(freq->tmpfile, sha1_file_name(freq->sha1));

	return freq->rename;
}