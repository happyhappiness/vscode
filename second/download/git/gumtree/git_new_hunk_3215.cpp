		return 0;
	}

	if (!strcmp("http.useragent", var))
		return git_config_string(&user_agent, var, value);

	if (!strcmp("http.emptyauth", var)) {
		curl_empty_auth = git_config_bool(var, value);
		return 0;
	}

	if (!strcmp("http.pinnedpubkey", var)) {
#if LIBCURL_VERSION_NUM >= 0x072c00
		return git_config_pathname(&ssl_pinnedkey, var, value);
#else
		warning(_("Public key pinning not supported with cURL < 7.44.0"));
		return 0;
#endif
	}

	/* Fall back on the default ones */
	return git_default_config(var, value, cb);
}

static void init_curl_http_auth(CURL *result)
{
	if (!http_auth.username) {
		if (curl_empty_auth)
			curl_easy_setopt(result, CURLOPT_USERPWD, ":");
		return;
	}

	credential_fill(&http_auth);

#if LIBCURL_VERSION_NUM >= 0x071301
	curl_easy_setopt(result, CURLOPT_USERNAME, http_auth.username);
	curl_easy_setopt(result, CURLOPT_PASSWORD, http_auth.password);
