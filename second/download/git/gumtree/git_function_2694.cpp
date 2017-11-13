static void init_curl_proxy_auth(CURL *result)
{
	if (proxy_auth.username) {
		if (!proxy_auth.password)
			credential_fill(&proxy_auth);
		set_proxyauth_name_password(result);
	}

	var_override(&http_proxy_authmethod, getenv("GIT_HTTP_PROXY_AUTHMETHOD"));

#if LIBCURL_VERSION_NUM >= 0x070a07 /* CURLOPT_PROXYAUTH and CURLAUTH_ANY */
	if (http_proxy_authmethod) {
		int i;
		for (i = 0; i < ARRAY_SIZE(proxy_authmethods); i++) {
			if (!strcmp(http_proxy_authmethod, proxy_authmethods[i].name)) {
				curl_easy_setopt(result, CURLOPT_PROXYAUTH,
						proxy_authmethods[i].curlauth_param);
				break;
			}
		}
		if (i == ARRAY_SIZE(proxy_authmethods)) {
			warning("unsupported proxy authentication method %s: using anyauth",
					http_proxy_authmethod);
			curl_easy_setopt(result, CURLOPT_PROXYAUTH, CURLAUTH_ANY);
		}
	}
	else
		curl_easy_setopt(result, CURLOPT_PROXYAUTH, CURLAUTH_ANY);
#endif
}