void setup_curl_trace(CURL *handle)
{
	if (!trace_want(&trace_curl))
		return;
	curl_easy_setopt(handle, CURLOPT_VERBOSE, 1L);
	curl_easy_setopt(handle, CURLOPT_DEBUGFUNCTION, curl_trace);
	curl_easy_setopt(handle, CURLOPT_DEBUGDATA, NULL);
}