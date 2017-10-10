		no_pragma_header);

	/*
	 * If there is data present from a previous transfer attempt,
	 * resume where it left off
	 */
	prev_posn = ftello(preq->packfile);
	if (prev_posn>0) {
		if (http_is_verbose)
			fprintf(stderr,
				"Resuming fetch of pack %s at byte %"PRIuMAX"\n",
				sha1_to_hex(target->sha1), (uintmax_t)prev_posn);
		http_opt_request_remainder(preq->slot->curl, prev_posn);
	}

	return preq;

abort:
	free(preq->url);
