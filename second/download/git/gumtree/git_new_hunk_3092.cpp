	if (!results)
		results = &results_buf;

	err = run_one_slot(slot, results);

	if (err != HTTP_OK && err != HTTP_REAUTH) {
		struct strbuf msg = STRBUF_INIT;
		if (results->http_code && results->http_code != 200)
			strbuf_addf(&msg, "HTTP %ld", results->http_code);
		if (results->curl_result != CURLE_OK) {
			if (msg.len)
				strbuf_addch(&msg, ' ');
			strbuf_addf(&msg, "curl %d", results->curl_result);
			if (curl_errorstr[0]) {
				strbuf_addch(&msg, ' ');
				strbuf_addstr(&msg, curl_errorstr);
			}
		}
		error("RPC failed; %s", msg.buf);
		strbuf_release(&msg);
	}

	return err;
}

static int probe_rpc(struct rpc_state *rpc, struct slot_results *results)
