	 * If we have successfully processed data from a previous fetch
	 * attempt, only fetch the data we don't already have.
	 */
	if (prev_posn>0) {
		if (http_is_verbose)
			fprintf(stderr,
				"Resuming fetch of object %s at byte %"PRIuMAX"\n",
				hex, (uintmax_t)prev_posn);
		http_opt_request_remainder(freq->slot->curl, prev_posn);
	}

	return freq;

abort:
	free(freq->url);
