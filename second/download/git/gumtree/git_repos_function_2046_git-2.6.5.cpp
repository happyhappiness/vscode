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
			}
		}
	}
	return 0;
}