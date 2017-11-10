static int http_request_reauth(const char *url,
			       void *result, int target,
			       struct http_get_options *options)
{
	int ret = http_request(url, result, target, options);

	if (ret != HTTP_OK && ret != HTTP_REAUTH)
		return ret;

	if (options && options->effective_url && options->base_url) {
		if (update_url_from_redirect(options->base_url,
					     url, options->effective_url)) {
			credential_from_url(&http_auth, options->base_url->buf);
			url = options->effective_url->buf;
		}
	}

	if (ret != HTTP_REAUTH)
		return ret;

	/*
	 * If we are using KEEP_ERROR, the previous request may have
	 * put cruft into our output stream; we should clear it out before
	 * making our next request. We only know how to do this for
	 * the strbuf case, but that is enough to satisfy current callers.
	 */
	if (options && options->keep_error) {
		switch (target) {
		case HTTP_REQUEST_STRBUF:
			strbuf_reset(result);
			break;
		default:
			die("BUG: HTTP_KEEP_ERROR is only supported with strbufs");
		}
	}

	credential_fill(&http_auth);

	return http_request(url, result, target, options);
}