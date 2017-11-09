static void start_fetch_loose(struct transfer_request *request)
{
	struct active_request_slot *slot;
	struct http_object_request *obj_req;

	obj_req = new_http_object_request(repo->url, request->obj->oid.hash);
	if (obj_req == NULL) {
		request->state = ABORTED;
		return;
	}

	slot = obj_req->slot;
	slot->callback_func = process_response;
	slot->callback_data = request;
	request->slot = slot;
	request->userData = obj_req;

	/* Try to get the request started, abort the request on error */
	request->state = RUN_FETCH_LOOSE;
	if (!start_active_slot(slot)) {
		fprintf(stderr, "Unable to start GET request\n");
		repo->can_update_info_refs = 0;
		release_http_object_request(obj_req);
		release_request(request);
	}
}