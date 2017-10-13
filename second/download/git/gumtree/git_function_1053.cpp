static int http_options(const char *var, const char *value, void *cb)
{
	if (!strcmp("http.sslverify", var)) {
		curl_ssl_verify = git_config_bool(var, value);
		return 0;
	}
	if (!strcmp("http.sslcipherlist", var))
		return git_config_string(&ssl_cipherlist, var, value);
	if (!strcmp("http.sslversion", var))
		return git_config_string(&ssl_version, var, value);
	if (!strcmp("http.sslcert", var))
		return git_config_string(&ssl_cert, var, value);
#if LIBCURL_VERSION_NUM >= 0x070903
	if (!strcmp("http.sslkey", var))
		return git_config_string(&ssl_key, var, value);
#endif
#if LIBCURL_VERSION_NUM >= 0x070908
	if (!strcmp("http.sslcapath", var))
		return git_config_pathname(&ssl_capath, var, value);
#endif
	if (!strcmp("http.sslcainfo", var))
		return git_config_pathname(&ssl_cainfo, var, value);
	if (!strcmp("http.sslcertpasswordprotected", var)) {
		ssl_cert_password_required = git_config_bool(var, value);
		return 0;
	}
	if (!strcmp("http.ssltry", var)) {
		curl_ssl_try = git_config_bool(var, value);
		return 0;
	}
	if (!strcmp("http.minsessions", var)) {
		min_curl_sessions = git_config_int(var, value);
#ifndef USE_CURL_MULTI
		if (min_curl_sessions > 1)
			min_curl_sessions = 1;
#endif
		return 0;
	}
#ifdef USE_CURL_MULTI
	if (!strcmp("http.maxrequests", var)) {
		max_requests = git_config_int(var, value);
		return 0;
	}
#endif
	if (!strcmp("http.lowspeedlimit", var)) {
		curl_low_speed_limit = (long)git_config_int(var, value);
		return 0;
	}
	if (!strcmp("http.lowspeedtime", var)) {
		curl_low_speed_time = (long)git_config_int(var, value);
		return 0;
	}

	if (!strcmp("http.noepsv", var)) {
		curl_ftp_no_epsv = git_config_bool(var, value);
		return 0;
	}
	if (!strcmp("http.proxy", var))
		return git_config_string(&curl_http_proxy, var, value);

	if (!strcmp("http.proxyauthmethod", var))
		return git_config_string(&http_proxy_authmethod, var, value);

	if (!strcmp("http.cookiefile", var))
		return git_config_pathname(&curl_cookie_file, var, value);
	if (!strcmp("http.savecookies", var)) {
		curl_save_cookies = git_config_bool(var, value);
		return 0;
	}

	if (!strcmp("http.postbuffer", var)) {
		http_post_buffer = git_config_ssize_t(var, value);
		if (http_post_buffer < 0)
			warning(_("negative value for http.postbuffer; defaulting to %d"), LARGE_PACKET_MAX);
		if (http_post_buffer < LARGE_PACKET_MAX)
			http_post_buffer = LARGE_PACKET_MAX;
		return 0;
	}

	if (!strcmp("http.useragent", var))
		return git_config_string(&user_agent, var, value);

	if (!strcmp("http.emptyauth", var)) {
		if (value && !strcmp("auto", value))
			curl_empty_auth = -1;
		else
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
#endif
	}

	if (!strcmp("http.extraheader", var)) {
		if (!value) {
			return config_error_nonbool(var);
		} else if (!*value) {
			curl_slist_free_all(extra_http_headers);
			extra_http_headers = NULL;
		} else {
			extra_http_headers =
				curl_slist_append(extra_http_headers, value);
		}
		return 0;
	}

	if (!strcmp("http.followredirects", var)) {
		if (value && !strcmp(value, "initial"))
			http_follow_config = HTTP_FOLLOW_INITIAL;
		else if (git_config_bool(var, value))
			http_follow_config = HTTP_FOLLOW_ALWAYS;
		else
			http_follow_config = HTTP_FOLLOW_NONE;
		return 0;
	}

	/* Fall back on the default ones */
	return git_default_config(var, value, cb);
}