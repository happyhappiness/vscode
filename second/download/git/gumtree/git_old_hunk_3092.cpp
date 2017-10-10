	if (!results)
		results = &results_buf;

	err = run_one_slot(slot, results);

	if (err != HTTP_OK && err != HTTP_REAUTH) {
		error("RPC failed; result=%d, HTTP code = %ld",
		      results->curl_result, results->http_code);
	}

	return err;
}

static int probe_rpc(struct rpc_state *rpc, struct slot_results *results)
