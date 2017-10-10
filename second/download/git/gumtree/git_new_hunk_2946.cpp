	/* Start the fetch */
	cdata->got_alternates = 0;

	if (walker->get_verbosely)
		fprintf(stderr, "Getting alternates list for %s\n", base);

	strbuf_addf(&url, "%s/objects/info/http-alternates", base);

	/*
	 * Use a callback to process the result, since another request
	 * may fail and need to have alternates loaded before continuing
	 */
	slot = get_active_slot();
	slot->callback_func = process_alternates_response;
	alt_req.walker = walker;
	slot->callback_data = &alt_req;

	curl_easy_setopt(slot->curl, CURLOPT_FILE, &buffer);
	curl_easy_setopt(slot->curl, CURLOPT_WRITEFUNCTION, fwrite_buffer);
	curl_easy_setopt(slot->curl, CURLOPT_URL, url.buf);

	alt_req.base = base;
	alt_req.url = &url;
	alt_req.buffer = &buffer;
	alt_req.http_specific = 1;
	alt_req.slot = slot;

	if (start_active_slot(slot))
		run_active_slot(slot);
	else
		cdata->got_alternates = -1;

	strbuf_release(&buffer);
	strbuf_release(&url);
}

static int fetch_indices(struct walker *walker, struct alt_base *repo)
{
	int ret;

