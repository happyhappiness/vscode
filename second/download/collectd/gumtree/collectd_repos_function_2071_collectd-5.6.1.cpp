static int dispatch_size (CURL *curl, CURLINFO info, value_list_t *vl)
{
	CURLcode code;
	value_t v;
	long raw;

	code = curl_easy_getinfo (curl, info, &raw);
	if (code != CURLE_OK)
		return -1;

	v.gauge = (double)raw;

	vl->values = &v;
	vl->values_len = 1;

	return plugin_dispatch_values (vl);
}