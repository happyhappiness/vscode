			strbuf_addch(&refs_url, '?');
		else
			strbuf_addch(&refs_url, '&');
		strbuf_addf(&refs_url, "service=%s", service);
	}

	memset(&options, 0, sizeof(options));
	options.content_type = &type;
	options.charset = &charset;
	options.effective_url = &effective_url;
	options.base_url = &url;
	options.no_cache = 1;
	options.keep_error = 1;

	http_ret = http_get_strbuf(refs_url.buf, &buffer, &options);
	switch (http_ret) {
	case HTTP_OK:
		break;
	case HTTP_MISSING_TARGET:
		show_http_message(&type, &charset, &buffer);
		die("repository '%s' not found", url.buf);
