static struct discovery *discover_refs(const char *service, int for_push)
{
	struct strbuf exp = STRBUF_INIT;
	struct strbuf type = STRBUF_INIT;
	struct strbuf charset = STRBUF_INIT;
	struct strbuf buffer = STRBUF_INIT;
	struct strbuf refs_url = STRBUF_INIT;
	struct strbuf effective_url = STRBUF_INIT;
	struct discovery *last = last_discovery;
	int http_ret, maybe_smart = 0;
	struct http_get_options http_options;

	if (last && !strcmp(service, last->service))
		return last;
	free_discovery(last);

	strbuf_addf(&refs_url, "%sinfo/refs", url.buf);
	if ((starts_with(url.buf, "http://") || starts_with(url.buf, "https://")) &&
	     git_env_bool("GIT_SMART_HTTP", 1)) {
		maybe_smart = 1;
		if (!strchr(url.buf, '?'))
			strbuf_addch(&refs_url, '?');
		else
			strbuf_addch(&refs_url, '&');
		strbuf_addf(&refs_url, "service=%s", service);
	}

	memset(&http_options, 0, sizeof(http_options));
	http_options.content_type = &type;
	http_options.charset = &charset;
	http_options.effective_url = &effective_url;
	http_options.base_url = &url;
	http_options.initial_request = 1;
	http_options.no_cache = 1;
	http_options.keep_error = 1;

	http_ret = http_get_strbuf(refs_url.buf, &buffer, &http_options);
	switch (http_ret) {
	case HTTP_OK:
		break;
	case HTTP_MISSING_TARGET:
		show_http_message(&type, &charset, &buffer);
		die("repository '%s' not found", url.buf);
	case HTTP_NOAUTH:
		show_http_message(&type, &charset, &buffer);
		die("Authentication failed for '%s'", url.buf);
	default:
		show_http_message(&type, &charset, &buffer);
		die("unable to access '%s': %s", url.buf, curl_errorstr);
	}

	if (options.verbosity && !starts_with(refs_url.buf, url.buf))
		warning(_("redirecting to %s"), url.buf);

	last= xcalloc(1, sizeof(*last_discovery));
	last->service = service;
	last->buf_alloc = strbuf_detach(&buffer, &last->len);
	last->buf = last->buf_alloc;

	strbuf_addf(&exp, "application/x-%s-advertisement", service);
	if (maybe_smart &&
	    (5 <= last->len && last->buf[4] == '#') &&
	    !strbuf_cmp(&exp, &type)) {
		char *line;

		/*
		 * smart HTTP response; validate that the service
		 * pkt-line matches our request.
		 */
		line = packet_read_line_buf(&last->buf, &last->len, NULL);

		strbuf_reset(&exp);
		strbuf_addf(&exp, "# service=%s", service);
		if (strcmp(line, exp.buf))
			die("invalid server response; got '%s'", line);
		strbuf_release(&exp);

		/* The header can include additional metadata lines, up
		 * until a packet flush marker.  Ignore these now, but
		 * in the future we might start to scan them.
		 */
		while (packet_read_line_buf(&last->buf, &last->len, NULL))
			;

		last->proto_git = 1;
	}

	if (last->proto_git)
		last->refs = parse_git_refs(last, for_push);
	else
		last->refs = parse_info_refs(last);

	strbuf_release(&refs_url);
	strbuf_release(&exp);
	strbuf_release(&type);
	strbuf_release(&charset);
	strbuf_release(&effective_url);
	strbuf_release(&buffer);
	last_discovery = last;
	return last;
}