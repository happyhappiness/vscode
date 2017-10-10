	}

	/*
	 * we turned off CURLOPT_FAILONERROR to avoid losing a
	 * persistent connection and got CURLE_OK.
	 */
	if (req->http_code == 404 && req->curl_result == CURLE_OK &&
			(starts_with(req->url, "http://") ||
			 starts_with(req->url, "https://")))
		req->curl_result = CURLE_HTTP_RETURNED_ERROR;

	if (obj_req->state == ABORTED) {
		ret = error("Request for %s aborted", hex);
	} else if (req->curl_result != CURLE_OK &&
		   req->http_code != 416) {
		if (missing_target(req))
