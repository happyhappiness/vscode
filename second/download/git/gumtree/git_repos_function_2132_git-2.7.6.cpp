static int http_fetch_pack(struct walker *walker, struct alt_base *repo, unsigned char *sha1)
{
	struct packed_git *target;
	int ret;
	struct slot_results results;
	struct http_pack_request *preq;

	if (fetch_indices(walker, repo))
		return -1;
	target = find_sha1_pack(sha1, repo->packs);
	if (!target)
		return -1;

	if (walker->get_verbosely) {
		fprintf(stderr, "Getting pack %s\n",
			sha1_to_hex(target->sha1));
		fprintf(stderr, " which contains %s\n",
			sha1_to_hex(sha1));
	}

	preq = new_http_pack_request(target, repo->base);
	if (preq == NULL)
		goto abort;
	preq->lst = &repo->packs;
	preq->slot->results = &results;

	if (start_active_slot(preq->slot)) {
		run_active_slot(preq->slot);
		if (results.curl_result != CURLE_OK) {
			error("Unable to get pack file %s\n%s", preq->url,
			      curl_errorstr);
			goto abort;
		}
	} else {
		error("Unable to start request");
		goto abort;
	}

	ret = finish_http_pack_request(preq);
	release_http_pack_request(preq);
	if (ret)
		return ret;

	return 0;

abort:
	return -1;
}