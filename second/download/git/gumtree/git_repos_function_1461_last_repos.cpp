static void set_proxyauth_name_password(CURL *result)
{
#if LIBCURL_VERSION_NUM >= 0x071301
		curl_easy_setopt(result, CURLOPT_PROXYUSERNAME,
			proxy_auth.username);
		curl_easy_setopt(result, CURLOPT_PROXYPASSWORD,
			proxy_auth.password);
#else
		struct strbuf s = STRBUF_INIT;

		strbuf_addstr_urlencode(&s, proxy_auth.username, 1);
		strbuf_addch(&s, ':');
		strbuf_addstr_urlencode(&s, proxy_auth.password, 1);
		curl_proxyuserpwd = strbuf_detach(&s, NULL);
		curl_easy_setopt(result, CURLOPT_PROXYUSERPWD, curl_proxyuserpwd);
#endif
}