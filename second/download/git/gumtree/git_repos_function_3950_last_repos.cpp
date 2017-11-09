static void start_mkcol(struct transfer_request *request)
{
	char *hex = oid_to_hex(&request->obj->oid);
	struct active_request_slot *slot;

	request->url = get_remote_object_url(repo->url, hex, 1);

	slot = get_active_slot();
	slot->callback_func = process_response;
	slot->callback_data = request;
	curl_setup_http_get(slot->curl, request->url, DAV_MKCOL);
	curl_easy_setopt(slot->curl, CURLOPT_ERRORBUFFER, request->errorstr);

	if (start_active_slot(slot)) {
		request->slot = slot;
		request->state = RUN_MKCOL;
	} else {
		request->state = ABORTED;
		FREE_AND_NULL(request->url);
	}
}