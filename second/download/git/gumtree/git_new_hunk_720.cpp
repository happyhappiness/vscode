		return;
	curl_easy_setopt(handle, CURLOPT_VERBOSE, 1L);
	curl_easy_setopt(handle, CURLOPT_DEBUGFUNCTION, curl_trace);
	curl_easy_setopt(handle, CURLOPT_DEBUGDATA, NULL);
}

static long get_curl_allowed_protocols(int from_user)
{
	long allowed_protocols = 0;

	if (is_transport_allowed("http", from_user))
		allowed_protocols |= CURLPROTO_HTTP;
	if (is_transport_allowed("https", from_user))
		allowed_protocols |= CURLPROTO_HTTPS;
	if (is_transport_allowed("ftp", from_user))
		allowed_protocols |= CURLPROTO_FTP;
	if (is_transport_allowed("ftps", from_user))
		allowed_protocols |= CURLPROTO_FTPS;

	return allowed_protocols;
}

static CURL *get_curl_handle(void)
{
	CURL *result = curl_easy_init();

	if (!result)
		die("curl_easy_init failed");

	if (!curl_ssl_verify) {
		curl_easy_setopt(result, CURLOPT_SSL_VERIFYPEER, 0);
