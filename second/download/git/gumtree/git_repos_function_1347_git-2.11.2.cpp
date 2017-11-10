void release_http_object_request(struct http_object_request *freq)
{
	if (freq->localfile != -1) {
		close(freq->localfile);
		freq->localfile = -1;
	}
	if (freq->url != NULL) {
		free(freq->url);
		freq->url = NULL;
	}
	if (freq->slot != NULL) {
		freq->slot->callback_func = NULL;
		freq->slot->callback_data = NULL;
		release_active_slot(freq->slot);
		freq->slot = NULL;
	}
}