struct curl_slist *http_copy_default_headers(void)
{
	struct curl_slist *headers = NULL, *h;

	for (h = extra_http_headers; h; h = h->next)
		headers = curl_slist_append(headers, h->data);

	return headers;
}