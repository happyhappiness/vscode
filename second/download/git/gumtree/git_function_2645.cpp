static int run_slot(struct active_request_slot *slot,
		    struct slot_results *results)
{
	int err;
	struct slot_results results_buf;

	if (!results)
		results = &results_buf;

	err = run_one_slot(slot, results);

	if (err != HTTP_OK && err != HTTP_REAUTH) {
		error("RPC failed; result=%d, HTTP code = %ld",
		      results->curl_result, results->http_code);
	}

	return err;
}