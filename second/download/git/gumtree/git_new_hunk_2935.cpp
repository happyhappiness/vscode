		request->url = NULL;
	}

	if (request->state == RUN_MKCOL) {
		if (request->curl_result == CURLE_OK ||
		    request->http_code == 405) {
			remote_dir_exists[request->obj->oid.hash[0]] = 1;
			start_put(request);
		} else {
			fprintf(stderr, "MKCOL %s failed, aborting (%d/%ld)\n",
				oid_to_hex(&request->obj->oid),
				request->curl_result, request->http_code);
			request->state = ABORTED;
			aborted = 1;
		}
	} else if (request->state == RUN_PUT) {
		if (request->curl_result == CURLE_OK) {
			start_move(request);
		} else {
			fprintf(stderr,	"PUT %s failed, aborting (%d/%ld)\n",
				oid_to_hex(&request->obj->oid),
				request->curl_result, request->http_code);
			request->state = ABORTED;
			aborted = 1;
		}
	} else if (request->state == RUN_MOVE) {
		if (request->curl_result == CURLE_OK) {
			if (push_verbosely)
				fprintf(stderr, "    sent %s\n",
					oid_to_hex(&request->obj->oid));
			request->obj->flags |= REMOTE;
			release_request(request);
		} else {
			fprintf(stderr, "MOVE %s failed, aborting (%d/%ld)\n",
				oid_to_hex(&request->obj->oid),
				request->curl_result, request->http_code);
			request->state = ABORTED;
			aborted = 1;
		}
	} else if (request->state == RUN_FETCH_LOOSE) {
		obj_req = (struct http_object_request *)request->userData;
