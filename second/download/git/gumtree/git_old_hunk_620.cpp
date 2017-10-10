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
