static int fill_active_slot(void *unused)
{
	struct transfer_request *request;

	if (aborted || !is_running_queue)
		return 0;

	for (request = request_queue_head; request; request = request->next) {
		if (request->state == NEED_FETCH) {
			start_fetch_loose(request);
			return 1;
		} else if (pushing && request->state == NEED_PUSH) {
			if (remote_dir_exists[request->obj->sha1[0]] == 1) {
				start_put(request);
			} else {
				start_mkcol(request);
			}
			return 1;
		}
	}
	return 0;
}