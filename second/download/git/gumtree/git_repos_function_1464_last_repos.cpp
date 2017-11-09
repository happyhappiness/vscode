static void set_curl_keepalive(CURL *c)
{
	curl_easy_setopt(c, CURLOPT_TCP_KEEPALIVE, 1);
}