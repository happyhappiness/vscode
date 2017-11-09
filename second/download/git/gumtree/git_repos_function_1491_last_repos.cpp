int run_one_slot(struct active_request_slot *slot,
		 struct slot_results *results)
{
	slot->results = results;
	if (!start_active_slot(slot)) {
		xsnprintf(curl_errorstr, sizeof(curl_errorstr),
			  "failed to start HTTP request");
		return HTTP_START_FAILED;
	}

	run_active_slot(slot);
	return handle_curl_result(results);
}