static void process_object_response(void *callback_data)
{
	struct object_request *obj_req =
		(struct object_request *)callback_data;
	struct walker *walker = obj_req->walker;
	struct walker_data *data = walker->data;
	struct alt_base *alt = data->alt;

	process_http_object_request(obj_req->req);
	obj_req->state = COMPLETE;

	/* Use alternates if necessary */
	if (missing_target(obj_req->req)) {
		fetch_alternates(walker, alt->base);
		if (obj_req->repo->next != NULL) {
			obj_req->repo =
				obj_req->repo->next;
			release_http_object_request(obj_req->req);
			start_object_request(walker, obj_req);
			return;
		}
	}

	finish_object_request(obj_req);
}