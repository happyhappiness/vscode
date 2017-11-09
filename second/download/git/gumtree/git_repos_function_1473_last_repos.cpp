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