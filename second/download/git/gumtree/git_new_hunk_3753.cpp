
static void abort_object_request(struct object_request *obj_req)
{
	release_object_request(obj_req);
}

static int fetch_object(struct walker *walker, unsigned char *sha1)
{
	char *hex = sha1_to_hex(sha1);
	int ret = 0;
	struct object_request *obj_req = NULL;
	struct http_object_request *req;
	struct list_head *pos, *head = &object_queue_head;

	list_for_each(pos, head) {
		obj_req = list_entry(pos, struct object_request, node);
		if (!hashcmp(obj_req->sha1, sha1))
			break;
	}
	if (obj_req == NULL)
		return error("Couldn't find request for %s in the queue", hex);

	if (has_sha1_file(obj_req->sha1)) {
		if (obj_req->req != NULL)
			abort_http_object_request(obj_req->req);
