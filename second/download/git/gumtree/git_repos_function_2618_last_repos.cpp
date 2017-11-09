static int fill_active_slot(struct walker *walker)
{
	struct object_request *obj_req;
	struct list_head *pos, *tmp, *head = &object_queue_head;

	list_for_each_safe(pos, tmp, head) {
		obj_req = list_entry(pos, struct object_request, node);
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