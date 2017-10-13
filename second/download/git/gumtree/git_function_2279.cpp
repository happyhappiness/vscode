static CURL *setup_curl(struct imap_server_conf *srvc)
{
	CURL *curl;
	struct strbuf path = STRBUF_INIT;

	if (curl_global_init(CURL_GLOBAL_ALL) != CURLE_OK)
		die("curl_global_init failed");

	curl = curl_easy_init();

	if (!curl)
		die("curl_easy_init failed");

	curl_easy_setopt(curl, CURLOPT_USERNAME, server.user);
	curl_easy_setopt(curl, CURLOPT_PASSWORD, server.pass);

	strbuf_addstr(&path, server.host);
	if (!path.len || path.buf[path.len - 1] != '/')
		strbuf_addch(&path, '/');
	strbuf_addstr(&path, server.folder);

	curl_easy_setopt(curl, CURLOPT_URL, path.buf);
	strbuf_release(&path);
	curl_easy_setopt(curl, CURLOPT_PORT, server.port);

	if (server.auth_method) {
#if LIBCURL_VERSION_NUM < 0x072200
		warning("No LOGIN_OPTIONS support in this cURL version");
#else
		struct strbuf auth = STRBUF_INIT;
		strbuf_addstr(&auth, "AUTH=");
		strbuf_addstr(&auth, server.auth_method);
		curl_easy_setopt(curl, CURLOPT_LOGIN_OPTIONS, auth.buf);
		strbuf_release(&auth);
#endif
	}

	if (!server.use_ssl)
		curl_easy_setopt(curl, CURLOPT_USE_SSL, (long)CURLUSESSL_TRY);

	curl_easy_setopt(curl, CURLOPT_SSL_VERIFYPEER, server.ssl_verify);
	curl_easy_setopt(curl, CURLOPT_SSL_VERIFYHOST, server.ssl_verify);

	curl_easy_setopt(curl, CURLOPT_READFUNCTION, fread_buffer);

	curl_easy_setopt(curl, CURLOPT_UPLOAD, 1L);

	if (0 < verbosity || getenv("GIT_CURL_VERBOSE"))
		curl_easy_setopt(curl, CURLOPT_VERBOSE, 1L);

	return curl;
}