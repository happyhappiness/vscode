static int http_request(const char *url,
			void *result, int target,
			const struct http_get_options *options)
{
	struct active_request_slot *slot;
	struct slot_results results;
	struct curl_slist *headers = NULL;
	struct strbuf buf = STRBUF_INIT;
	int ret;

	slot = get_active_slot();
	curl_easy_setopt(slot->curl, CURLOPT_HTTPGET, 1);

	if (result == NULL) {
		curl_easy_setopt(slot->curl, CURLOPT_NOBODY, 1);
	} else {
		curl_easy_setopt(slot->curl, CURLOPT_NOBODY, 0);
		curl_easy_setopt(slot->curl, CURLOPT_FILE, result);

		if (target == HTTP_REQUEST_FILE) {
			long posn = ftell(result);
			curl_easy_setopt(slot->curl, CURLOPT_WRITEFUNCTION,
					 fwrite);
			if (posn > 0) {
				strbuf_addf(&buf, "Range: bytes=%ld-", posn);
				headers = curl_slist_append(headers, buf.buf);
				strbuf_reset(&buf);
			}
		} else
			curl_easy_setopt(slot->curl, CURLOPT_WRITEFUNCTION,
					 fwrite_buffer);
	}

	strbuf_addstr(&buf, "Pragma:");
	if (options && options->no_cache)
		strbuf_addstr(&buf, " no-cache");
	if (options && options->keep_error)
		curl_easy_setopt(slot->curl, CURLOPT_FAILONERROR, 0);

	headers = curl_slist_append(headers, buf.buf);

	curl_easy_setopt(slot->curl, CURLOPT_URL, url);
	curl_easy_setopt(slot->curl, CURLOPT_HTTPHEADER, headers);
	curl_easy_setopt(slot->curl, CURLOPT_ENCODING, "gzip");

	ret = run_one_slot(slot, &results);

	if (options && options->content_type)
		curlinfo_strbuf(slot->curl, CURLINFO_CONTENT_TYPE,
				options->content_type);

	if (options && options->effective_url)
		curlinfo_strbuf(slot->curl, CURLINFO_EFFECTIVE_URL,
				options->effective_url);

	curl_slist_free_all(headers);
	strbuf_release(&buf);

	return ret;
}