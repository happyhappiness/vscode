void step_active_slots(void)
{
	int num_transfers;
	CURLMcode curlm_result;

	do {
		curlm_result = curl_multi_perform(curlm, &num_transfers);
	} while (curlm_result == CURLM_CALL_MULTI_PERFORM);
	if (num_transfers < active_requests) {
		process_curl_messages();
		fill_active_slots();
	}
}