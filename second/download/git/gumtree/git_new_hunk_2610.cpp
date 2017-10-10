	curl_easy_setopt(result, CURLOPT_HTTPAUTH, CURLAUTH_ANY);
#endif

	if (http_proactive_auth)
		init_curl_http_auth(result);

	if (getenv("GIT_SSL_VERSION"))
		ssl_version = getenv("GIT_SSL_VERSION");
	if (ssl_version && *ssl_version) {
		int i;
		for (i = 0; i < ARRAY_SIZE(sslversions); i++) {
			if (!strcmp(ssl_version, sslversions[i].name)) {
				curl_easy_setopt(result, CURLOPT_SSLVERSION,
						 sslversions[i].ssl_version);
				break;
			}
		}
		if (i == ARRAY_SIZE(sslversions))
			warning("unsupported ssl version %s: using default",
				ssl_version);
	}

	if (getenv("GIT_SSL_CIPHER_LIST"))
		ssl_cipherlist = getenv("GIT_SSL_CIPHER_LIST");
	if (ssl_cipherlist != NULL && *ssl_cipherlist)
		curl_easy_setopt(result, CURLOPT_SSL_CIPHER_LIST,
				ssl_cipherlist);

	if (ssl_cert != NULL)
		curl_easy_setopt(result, CURLOPT_SSLCERT, ssl_cert);
