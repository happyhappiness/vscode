		return 0;
	}

	if (!strcmp("http.useragent", var))
		return git_config_string(&user_agent, var, value);

	/* Fall back on the default ones */
	return git_default_config(var, value, cb);
}

static void init_curl_http_auth(CURL *result)
{
	if (!http_auth.username)
		return;

	credential_fill(&http_auth);

#if LIBCURL_VERSION_NUM >= 0x071301
	curl_easy_setopt(result, CURLOPT_USERNAME, http_auth.username);
	curl_easy_setopt(result, CURLOPT_PASSWORD, http_auth.password);
