	curl_easy_setopt(result, CURLOPT_NETRC, CURL_NETRC_OPTIONAL);
#endif
#ifdef LIBCURL_CAN_HANDLE_AUTH_ANY
	curl_easy_setopt(result, CURLOPT_HTTPAUTH, CURLAUTH_ANY);
#endif

	if (http_proactive_auth)
		init_curl_http_auth(result);

	if (getenv("GIT_SSL_VERSION"))
		ssl_version = getenv("GIT_SSL_VERSION");
	if (ssl_version && *ssl_version) {
