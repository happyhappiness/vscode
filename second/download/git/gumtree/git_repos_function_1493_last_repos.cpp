static CURLcode curlinfo_strbuf(CURL *curl, CURLINFO info, struct strbuf *buf)
{
	char *ptr;
	CURLcode ret;

	strbuf_reset(buf);
	ret = curl_easy_getinfo(curl, info, &ptr);
	if (!ret && ptr)
		strbuf_addstr(buf, ptr);
	return ret;
}