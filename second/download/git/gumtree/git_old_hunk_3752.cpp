
	finish_object_request(obj_req);
}

static void release_object_request(struct object_request *obj_req)
{
	struct object_request *entry = object_queue_head;

	if (obj_req->req !=NULL && obj_req->req->localfile != -1)
		error("fd leakage in release: %d", obj_req->req->localfile);
	if (obj_req == object_queue_head) {
		object_queue_head = obj_req->next;
	} else {
		while (entry->next != NULL && entry->next != obj_req)
			entry = entry->next;
		if (entry->next == obj_req)
			entry->next = entry->next->next;
	}

	free(obj_req);
}

#ifdef USE_CURL_MULTI
static int fill_active_slot(struct walker *walker)
{
	struct object_request *obj_req;

	for (obj_req = object_queue_head; obj_req; obj_req = obj_req->next) {
		if (obj_req->state == WAITING) {
			if (has_sha1_file(obj_req->sha1))
				obj_req->state = COMPLETE;
			else {
				start_object_request(walker, obj_req);
				return 1;
