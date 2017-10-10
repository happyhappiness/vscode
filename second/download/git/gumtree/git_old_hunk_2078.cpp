
	fprintf(stderr,	"Fetching pack %s\n", sha1_to_hex(target->sha1));
	fprintf(stderr, " which contains %s\n", sha1_to_hex(request->obj->sha1));

	preq = new_http_pack_request(target, repo->url);
	if (preq == NULL) {
		release_http_pack_request(preq);
		repo->can_update_info_refs = 0;
		return;
	}
	preq->lst = &repo->packs;

	/* Make sure there isn't another open request for this pack */
