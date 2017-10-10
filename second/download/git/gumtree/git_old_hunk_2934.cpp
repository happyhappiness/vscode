{
	struct packed_git *target;

	struct transfer_request *check_request = request_queue_head;
	struct http_pack_request *preq;

	target = find_sha1_pack(request->obj->sha1, repo->packs);
	if (!target) {
		fprintf(stderr, "Unable to fetch %s, will not be able to update server info refs\n", sha1_to_hex(request->obj->sha1));
		repo->can_update_info_refs = 0;
		release_request(request);
		return;
	}

	fprintf(stderr,	"Fetching pack %s\n", sha1_to_hex(target->sha1));
	fprintf(stderr, " which contains %s\n", sha1_to_hex(request->obj->sha1));

	preq = new_http_pack_request(target, repo->url);
	if (preq == NULL) {
		repo->can_update_info_refs = 0;
		return;
	}
