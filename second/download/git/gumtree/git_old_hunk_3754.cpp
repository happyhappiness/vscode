
	if (req->localfile != -1) {
		close(req->localfile);
		req->localfile = -1;
	}

	if (obj_req->state == ABORTED) {
		ret = error("Request for %s aborted", hex);
	} else if (req->curl_result != CURLE_OK &&
		   req->http_code != 416) {
		if (missing_target(req))
			ret = -1; /* Be silent, it is probably in a pack. */
