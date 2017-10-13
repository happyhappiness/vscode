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

	if (http_proactive_auth)
		init_curl_http_auth(result);

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
		curl_easy_setopt(result, CURLOPT_VERBOSE, 1);

	curl_easy_setopt(result, CURLOPT_USERAGENT,
		user_agent ? user_agent : git_user_agent());

	if (curl_ftp_no_epsv)
		curl_easy_setopt(result, CURLOPT_FTP_USE_EPSV, 0);

#ifdef CURLOPT_USE_SSL
	if (curl_ssl_try)
		curl_easy_setopt(result, CURLOPT_USE_SSL, CURLUSESSL_TRY);
#endif

	if (curl_http_proxy) {
		curl_easy_setopt(result, CURLOPT_PROXY, curl_http_proxy);
		curl_easy_setopt(result, CURLOPT_PROXYAUTH, CURLAUTH_ANY);
	}

	set_curl_keepalive(result);

	return result;
}