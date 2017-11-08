static int fetch_object(struct walker *walker, unsigned char *sha1)
{
	char *hex = sha1_to_hex(sha1);
	int ret = 0;
	struct object_request *obj_req = NULL;
	struct http_object_request *req;
	struct list_head *pos, *head = &object_queue_head;

	list_for_each(pos, head) {
		obj_req = list_entry(pos, struct object_request, node);
		if (!hashcmp(obj_req->sha1, sha1))
			break;
	}
	if (obj_req == NULL)
		return error("Couldn't find request for %s in the queue", hex);

	if (has_sha1_file(obj_req->sha1)) {
		if (obj_req->req != NULL)
			abort_http_object_request(obj_req->req);
		abort_object_request(obj_req);
		return 0;
	}

#ifdef USE_CURL_MULTI
	while (obj_req->state == WAITING)
		step_active_slots();
#else
	start_object_request(walker, obj_req);
#endif

	/*
	 * obj_req->req might change when fetching alternates in the callback
	 * process_object_response; therefore, the "shortcut" variable, req,
	 * is used only after we're done with slots.
	 */
	while (obj_req->state == ACTIVE)
		run_active_slot(obj_req->req->slot);

	req = obj_req->req;

	if (req->localfile != -1) {
		close(req->localfile);
		req->localfile = -1;
	}

	/*
	 * we turned off CURLOPT_FAILONERROR to avoid losing a
	 * persistent connection and got CURLE_OK.
	 */
	if (req->http_code >= 300 && req->curl_result == CURLE_OK &&
			(starts_with(req->url, "http://") ||
			 starts_with(req->url, "https://"))) {
		req->curl_result = CURLE_HTTP_RETURNED_ERROR;
		xsnprintf(req->errorstr, sizeof(req->errorstr),
			  "HTTP request failed");
	}

	if (obj_req->state == ABORTED) {
		ret = error("Request for %s aborted", hex);
	} else if (req->curl_result != CURLE_OK &&
		   req->http_code != 416) {
		if (missing_target(req))
			ret = -1; /* Be silent, it is probably in a pack. */
		else
			ret = error("%s (curl_result = %d, http_code = %ld, sha1 = %s)",
				    req->errorstr, req->curl_result,
				    req->http_code, hex);
	} else if (req->zret != Z_STREAM_END) {
		walker->corrupt_object_found++;
		ret = error("File %s (%s) corrupt", hex, req->url);
	} else if (hashcmp(obj_req->sha1, req->real_sha1)) {
		ret = error("File %s has bad hash", hex);
	} else if (req->rename < 0) {
		ret = error("unable to write sha1 filename %s",
			    sha1_file_name(req->sha1));
	}

	release_http_object_request(req);
	release_object_request(obj_req);
	return ret;
}