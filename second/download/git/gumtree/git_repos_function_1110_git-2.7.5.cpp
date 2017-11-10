struct http_pack_request *new_http_pack_request(
	struct packed_git *target, const char *base_url)
{
	off_t prev_posn = 0;
	struct strbuf buf = STRBUF_INIT;
	struct http_pack_request *preq;

	preq = xcalloc(1, sizeof(*preq));
	preq->target = target;

	end_url_with_slash(&buf, base_url);
	strbuf_addf(&buf, "objects/pack/pack-%s.pack",
		sha1_to_hex(target->sha1));
	preq->url = strbuf_detach(&buf, NULL);

	snprintf(preq->tmpfile, sizeof(preq->tmpfile), "%s.temp",
		sha1_pack_name(target->sha1));
	preq->packfile = fopen(preq->tmpfile, "a");
	if (!preq->packfile) {
		error("Unable to open local file %s for pack",
		      preq->tmpfile);
		goto abort;
	}

	preq->slot = get_active_slot();
	curl_easy_setopt(preq->slot->curl, CURLOPT_FILE, preq->packfile);
	curl_easy_setopt(preq->slot->curl, CURLOPT_WRITEFUNCTION, fwrite);
	curl_easy_setopt(preq->slot->curl, CURLOPT_URL, preq->url);
	curl_easy_setopt(preq->slot->curl, CURLOPT_HTTPHEADER,
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
	free(preq);
	return NULL;
}