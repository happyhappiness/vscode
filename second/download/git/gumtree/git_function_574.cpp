static CURL *get_curl_handle(void)
{
	CURL *result = curl_easy_init();
	long allowed_protocols = 0;

	if (!result)
		die("curl_easy_init failed");

	if (!curl_ssl_verify) {
		curl_easy_setopt(result, CURLOPT_SSL_VERIFYPEER, 0);
		curl_easy_setopt(result, CURLOPT_SSL_VERIFYHOST, 0);
	} else {
		/* Verify authenticity of the peer's certificate */
		curl_easy_setopt(result, CURLOPT_SSL_VERIFYPEER, 1);
		/* The name in the cert must match whom we tried to connect */
		curl_easy_setopt(result, CURLOPT_SSL_VERIFYHOST, 2);
	}

#if LIBCURL_VERSION_NUM >= 0x070907
	curl_easy_setopt(result, CURLOPT_NETRC, CURL_NETRC_OPTIONAL);
#endif
#ifdef LIBCURL_CAN_HANDLE_AUTH_ANY
	curl_easy_setopt(result, CURLOPT_HTTPAUTH, CURLAUTH_ANY);
#endif

#if LIBCURL_VERSION_NUM >= 0x071600
	if (curl_deleg) {
		int i;
		for (i = 0; i < ARRAY_SIZE(curl_deleg_levels); i++) {
			if (!strcmp(curl_deleg, curl_deleg_levels[i].name)) {
				curl_easy_setopt(result, CURLOPT_GSSAPI_DELEGATION,
						curl_deleg_levels[i].curl_deleg_param);
				break;
			}
		}
		if (i == ARRAY_SIZE(curl_deleg_levels))
			warning("Unknown delegation method '%s': using default",
				curl_deleg);
	}
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
	if (has_cert_password())
		curl_easy_setopt(result, CURLOPT_KEYPASSWD, cert_auth.password);
#if LIBCURL_VERSION_NUM >= 0x070903
	if (ssl_key != NULL)
		curl_easy_setopt(result, CURLOPT_SSLKEY, ssl_key);
#endif
#if LIBCURL_VERSION_NUM >= 0x070908
	if (ssl_capath != NULL)
		curl_easy_setopt(result, CURLOPT_CAPATH, ssl_capath);
#endif
#if LIBCURL_VERSION_NUM >= 0x072c00
	if (ssl_pinnedkey != NULL)
		curl_easy_setopt(result, CURLOPT_PINNEDPUBLICKEY, ssl_pinnedkey);
#endif
	if (ssl_cainfo != NULL)
		curl_easy_setopt(result, CURLOPT_CAINFO, ssl_cainfo);

	if (curl_low_speed_limit > 0 && curl_low_speed_time > 0) {
		curl_easy_setopt(result, CURLOPT_LOW_SPEED_LIMIT,
				 curl_low_speed_limit);
		curl_easy_setopt(result, CURLOPT_LOW_SPEED_TIME,
				 curl_low_speed_time);
	}

	curl_easy_setopt(result, CURLOPT_FOLLOWLOCATION, 1);
	curl_easy_setopt(result, CURLOPT_MAXREDIRS, 20);
#if LIBCURL_VERSION_NUM >= 0x071301
	curl_easy_setopt(result, CURLOPT_POSTREDIR, CURL_REDIR_POST_ALL);
#elif LIBCURL_VERSION_NUM >= 0x071101
	curl_easy_setopt(result, CURLOPT_POST301, 1);
#endif
#if LIBCURL_VERSION_NUM >= 0x071304
	if (is_transport_allowed("http"))
		allowed_protocols |= CURLPROTO_HTTP;
	if (is_transport_allowed("https"))
		allowed_protocols |= CURLPROTO_HTTPS;
	if (is_transport_allowed("ftp"))
		allowed_protocols |= CURLPROTO_FTP;
	if (is_transport_allowed("ftps"))
		allowed_protocols |= CURLPROTO_FTPS;
	curl_easy_setopt(result, CURLOPT_REDIR_PROTOCOLS, allowed_protocols);
#else
	if (transport_restrict_protocols())
		warning("protocol restrictions not applied to curl redirects because\n"
			"your curl version is too old (>= 7.19.4)");
#endif
	if (getenv("GIT_CURL_VERBOSE"))
		curl_easy_setopt(result, CURLOPT_VERBOSE, 1L);
	setup_curl_trace(result);

	curl_easy_setopt(result, CURLOPT_USERAGENT,
		user_agent ? user_agent : git_user_agent());

	if (curl_ftp_no_epsv)
		curl_easy_setopt(result, CURLOPT_FTP_USE_EPSV, 0);

#ifdef CURLOPT_USE_SSL
	if (curl_ssl_try)
		curl_easy_setopt(result, CURLOPT_USE_SSL, CURLUSESSL_TRY);
#endif

	/*
	 * CURL also examines these variables as a fallback; but we need to query
	 * them here in order to decide whether to prompt for missing password (cf.
	 * init_curl_proxy_auth()).
	 *
	 * Unlike many other common environment variables, these are historically
	 * lowercase only. It appears that CURL did not know this and implemented
	 * only uppercase variants, which was later corrected to take both - with
	 * the exception of http_proxy, which is lowercase only also in CURL. As
	 * the lowercase versions are the historical quasi-standard, they take
	 * precedence here, as in CURL.
	 */
	if (!curl_http_proxy) {
		if (http_auth.protocol && !strcmp(http_auth.protocol, "https")) {
			var_override(&curl_http_proxy, getenv("HTTPS_PROXY"));
			var_override(&curl_http_proxy, getenv("https_proxy"));
		} else {
			var_override(&curl_http_proxy, getenv("http_proxy"));
		}
		if (!curl_http_proxy) {
			var_override(&curl_http_proxy, getenv("ALL_PROXY"));
			var_override(&curl_http_proxy, getenv("all_proxy"));
		}
	}

	if (curl_http_proxy) {
		curl_easy_setopt(result, CURLOPT_PROXY, curl_http_proxy);
#if LIBCURL_VERSION_NUM >= 0x071800
		if (starts_with(curl_http_proxy, "socks5h"))
			curl_easy_setopt(result,
				CURLOPT_PROXYTYPE, CURLPROXY_SOCKS5_HOSTNAME);
		else if (starts_with(curl_http_proxy, "socks5"))
			curl_easy_setopt(result,
				CURLOPT_PROXYTYPE, CURLPROXY_SOCKS5);
		else if (starts_with(curl_http_proxy, "socks4a"))
			curl_easy_setopt(result,
				CURLOPT_PROXYTYPE, CURLPROXY_SOCKS4A);
		else if (starts_with(curl_http_proxy, "socks"))
			curl_easy_setopt(result,
				CURLOPT_PROXYTYPE, CURLPROXY_SOCKS4);
#endif
		if (strstr(curl_http_proxy, "://"))
			credential_from_url(&proxy_auth, curl_http_proxy);
		else {
			struct strbuf url = STRBUF_INIT;
			strbuf_addf(&url, "http://%s", curl_http_proxy);
			credential_from_url(&proxy_auth, url.buf);
			strbuf_release(&url);
		}

		curl_easy_setopt(result, CURLOPT_PROXY, proxy_auth.host);
#if LIBCURL_VERSION_NUM >= 0x071304
		var_override(&curl_no_proxy, getenv("NO_PROXY"));
		var_override(&curl_no_proxy, getenv("no_proxy"));
		curl_easy_setopt(result, CURLOPT_NOPROXY, curl_no_proxy);
#endif
	}
	init_curl_proxy_auth(result);

	set_curl_keepalive(result);

	return result;
}