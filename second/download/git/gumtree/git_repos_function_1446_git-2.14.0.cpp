static void finish_active_slot(struct active_request_slot *slot)
{
	closedown_active_slot(slot);
	curl_easy_getinfo(slot->curl, CURLINFO_HTTP_CODE, &slot->http_code);

	if (slot->finished != NULL)
		(*slot->finished) = 1;

	/* Store slot results so they can be read after the slot is reused */
	if (slot->results != NULL) {
		slot->results->curl_result = slot->curl_result;
		slot->results->http_code = slot->http_code;
#if LIBCURL_VERSION_NUM >= 0x070a08
		curl_easy_getinfo(slot->curl, CURLINFO_HTTPAUTH_AVAIL,
				  &slot->results->auth_avail);
#else
		slot->results->auth_avail = 0;
#endif

		curl_easy_getinfo(slot->curl, CURLINFO_HTTP_CONNECTCODE,
			&slot->results->http_connectcode);
	}

	/* Run callback if appropriate */
	if (slot->callback_func != NULL)
		slot->callback_func(slot->callback_data);
}