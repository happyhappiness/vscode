void process_http_object_request(struct http_object_request *freq)
{
	if (freq->slot == NULL)
		return;
	freq->curl_result = freq->slot->curl_result;
	freq->http_code = freq->slot->http_code;
	freq->slot = NULL;
}