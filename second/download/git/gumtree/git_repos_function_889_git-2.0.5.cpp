void http_init(struct remote *remote, const char *url, int proactive_auth)
{
	char *low_speed_limit;
	char *low_speed_time;
	char *normalized_url;
	struct urlmatch_config config = { STRING_LIST_INIT_DUP };

	config.section = "http";
	config.key = NULL;
	config.collect_fn = http_options;
	config.cascade_fn = git_default_config;
	config.cb = NULL;

	http_is_verbose = 0;
	normalized_url = url_normalize(url, &config.url);

	git_config(urlmatch_config_entry, &config);
	free(normalized_url);

	curl_global_init(CURL_GLOBAL_ALL);

	http_proactive_auth = proactive_auth;

	if (remote && remote->http_proxy)
		curl_http_proxy = xstrdup(remote->http_proxy);

	pragma_header = curl_slist_append(pragma_header, "Pragma: no-cache");
	no_pragma_header = curl_slist_append(no_pragma_header, "Pragma:");

#ifdef USE_CURL_MULTI
	{
		char *http_max_requests = getenv("GIT_HTTP_MAX_REQUESTS");
		if (http_max_requests != NULL)
			max_requests = atoi(http_max_requests);
	}

	curlm = curl_multi_init();
	if (curlm == NULL) {
		fprintf(stderr, "Error creating curl multi handle.\n");
		exit(1);
	}
#endif

	if (getenv("GIT_SSL_NO_VERIFY"))
		curl_ssl_verify = 0;

	set_from_env(&ssl_cert, "GIT_SSL_CERT");
#if LIBCURL_VERSION_NUM >= 0x070903
	set_from_env(&ssl_key, "GIT_SSL_KEY");
#endif
#if LIBCURL_VERSION_NUM >= 0x070908
	set_from_env(&ssl_capath, "GIT_SSL_CAPATH");
#endif
	set_from_env(&ssl_cainfo, "GIT_SSL_CAINFO");

	set_from_env(&user_agent, "GIT_HTTP_USER_AGENT");

	low_speed_limit = getenv("GIT_HTTP_LOW_SPEED_LIMIT");
	if (low_speed_limit != NULL)
		curl_low_speed_limit = strtol(low_speed_limit, NULL, 10);
	low_speed_time = getenv("GIT_HTTP_LOW_SPEED_TIME");
	if (low_speed_time != NULL)
		curl_low_speed_time = strtol(low_speed_time, NULL, 10);

	if (curl_ssl_verify == -1)
		curl_ssl_verify = 1;

	curl_session_count = 0;
#ifdef USE_CURL_MULTI
	if (max_requests < 1)
		max_requests = DEFAULT_MAX_REQUESTS;
#endif

	if (getenv("GIT_CURL_FTP_NO_EPSV"))
		curl_ftp_no_epsv = 1;

	if (url) {
		credential_from_url(&http_auth, url);
		if (!ssl_cert_password_required &&
		    getenv("GIT_SSL_CERT_PASSWORD_PROTECTED") &&
		    starts_with(url, "https://"))
			ssl_cert_password_required = 1;
	}

#ifndef NO_CURL_EASY_DUPHANDLE
	curl_default = get_curl_handle();
#endif
}