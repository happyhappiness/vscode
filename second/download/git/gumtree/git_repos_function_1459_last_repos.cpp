static void init_curl_http_auth(CURL *result)
{
	if (!http_auth.username || !*http_auth.username) {
		if (curl_empty_auth_enabled())
			curl_easy_setopt(result, CURLOPT_USERPWD, ":");
		return;
	}

	credential_fill(&http_auth);

#if LIBCURL_VERSION_NUM >= 0x071301
	curl_easy_setopt(result, CURLOPT_USERNAME, http_auth.username);
	curl_easy_setopt(result, CURLOPT_PASSWORD, http_auth.password);
#else
	{
		static struct strbuf up = STRBUF_INIT;
		/*
		 * Note that we assume we only ever have a single set of
		 * credentials in a given program run, so we do not have
		 * to worry about updating this buffer, only setting its
		 * initial value.
		 */
		if (!up.len)
			strbuf_addf(&up, "%s:%s",
				http_auth.username, http_auth.password);
		curl_easy_setopt(result, CURLOPT_USERPWD, up.buf);
	}
#endif
}