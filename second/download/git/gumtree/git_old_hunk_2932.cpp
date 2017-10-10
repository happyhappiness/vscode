		no_pragma_header);

	/*
	 * If there is data present from a previous transfer attempt,
	 * resume where it left off
	 */
	prev_posn = ftell(preq->packfile);
	if (prev_posn>0) {
		if (http_is_verbose)
			fprintf(stderr,
				"Resuming fetch of pack %s at byte %ld\n",
				sha1_to_hex(target->sha1), prev_posn);
		sprintf(range, "Range: bytes=%ld-", prev_posn);
		preq->range_header = curl_slist_append(NULL, range);
		curl_easy_setopt(preq->slot->curl, CURLOPT_HTTPHEADER,
			preq->range_header);
	}

	return preq;

abort:
	free(preq->url);
