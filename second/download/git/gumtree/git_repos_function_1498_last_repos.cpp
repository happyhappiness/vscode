static void http_opt_request_remainder(CURL *curl, off_t pos)
{
	char buf[128];
	xsnprintf(buf, sizeof(buf), "%"PRIuMAX"-", (uintmax_t)pos);
	curl_easy_setopt(curl, CURLOPT_RANGE, buf);
}