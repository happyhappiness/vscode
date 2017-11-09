static int http_request(const char *url,
			void *result, int target,
			const struct http_get_options *options)
{
	struct active_request_slot *slot;
	struct slot_results results;
	struct curl_slist *headers = http_copy_default_headers();
	struct strbuf buf = STRBUF_INIT;
	const char *accept_language;
	int ret;

	slot = get_active_slot();
	curl_easy_setopt(slot->curl, CURLOPT_HTTPGET, 1);

	if (result == NULL) {
		curl_easy_setopt(slot->curl, CURLOPT_NOBODY, 1);
	} else {
		curl_easy_setopt(slot->curl, CURLOPT_NOBODY, 0);
		curl_easy_setopt(slot->curl, CURLOPT_FILE, result);

		if (target == HTTP_REQUEST_FILE) {
			off_t posn = ftello(result);
			curl_easy_setopt(slot->curl, CURLOPT_WRITEFUNCTION,
					 fwrite);
			if (posn > 0)
				http_opt_request_remainder(slot->curl, posn);
		} else
			curl_easy_setopt(slot->curl, CURLOPT_WRITEFUNCTION,
					 fwrite_buffer);
	}

	accept_language = get_accept_language();

	if (accept_language)
		headers = curl_slist_append(headers, accept_language);

	strbuf_addstr(&buf, "Pragma:");
	if (options && options->no_cache)
		strbuf_addstr(&buf, " no-cache");
	if (options && options->keep_error)
		curl_easy_setopt(slot->curl, CURLOPT_FAILONERROR, 0);
	if (options && options->initial_request &&
	    http_follow_config == HTTP_FOLLOW_INITIAL)
		curl_easy_setopt(slot->curl, CURLOPT_FOLLOWLOCATION, 1);

	headers = curl_slist_append(headers, buf.buf);

	curl_easy_setopt(slot->curl, CURLOPT_URL, url);
	curl_easy_setopt(slot->curl, CURLOPT_HTTPHEADER, headers);
	curl_easy_setopt(slot->curl, CURLOPT_ENCODING, "gzip");

	ret = run_one_slot(slot, &results);

	if (options && options->content_type) {
		struct strbuf raw = STRBUF_INIT;
		curlinfo_strbuf(slot->curl, CURLINFO_CONTENT_TYPE, &raw);
		extract_content_type(&raw, options->content_type,
				     options->charset);
		strbuf_release(&raw);
	}

	if (options && options->effective_url)
		curlinfo_strbuf(slot->curl, CURLINFO_EFFECTIVE_URL,
				options->effective_url);

	curl_slist_free_all(headers);
	strbuf_release(&buf);

	return ret;
}