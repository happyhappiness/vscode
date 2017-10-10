	if (!curl)
		die("curl_easy_init failed");

	curl_easy_setopt(curl, CURLOPT_USERNAME, server.user);
	curl_easy_setopt(curl, CURLOPT_PASSWORD, server.pass);

	strbuf_addstr(&path, server.use_ssl ? "imaps://" : "imap://");
	strbuf_addstr(&path, server.host);
	if (!path.len || path.buf[path.len - 1] != '/')
		strbuf_addch(&path, '/');
	strbuf_addstr(&path, server.folder);

	curl_easy_setopt(curl, CURLOPT_URL, path.buf);
