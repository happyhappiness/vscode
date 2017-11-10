static void add_fetch_request(struct object *obj)
{
	struct transfer_request *request;

	check_locks();

	/*
	 * Don't fetch the object if it's known to exist locally
	 * or is already in the request queue
	 */
	if (remote_dir_exists[obj->oid.hash[0]] == -1)
		get_remote_object_list(obj->oid.hash[0]);
	if (obj->flags & (LOCAL | FETCHING))
		return;

	obj->flags |= FETCHING;
	request = xmalloc(sizeof(*request));
	request->obj = obj;
	request->url = NULL;
	request->lock = NULL;
	request->headers = NULL;
	request->state = NEED_FETCH;
	request->next = request_queue_head;
	request_queue_head = request;

#ifdef USE_CURL_MULTI
	fill_active_slots();
	step_active_slots();
#endif
}