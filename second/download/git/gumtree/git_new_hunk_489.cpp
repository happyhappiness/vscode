
	if (!strcmp("http.emptyauth", var)) {
		curl_empty_auth = git_config_bool(var, value);
		return 0;
	}

	if (!strcmp("http.delegation", var)) {
#if LIBCURL_VERSION_NUM >= 0x071600
		return git_config_string(&curl_deleg, var, value);
#else
		warning(_("Delegation control is not supported with cURL < 7.22.0"));
		return 0;
#endif
	}

	if (!strcmp("http.pinnedpubkey", var)) {
#if LIBCURL_VERSION_NUM >= 0x072c00
		return git_config_pathname(&ssl_pinnedkey, var, value);
#else
		warning(_("Public key pinning not supported with cURL < 7.44.0"));
		return 0;
