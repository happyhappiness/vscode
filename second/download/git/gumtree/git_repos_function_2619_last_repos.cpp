static void prefetch(struct walker *walker, unsigned char *sha1)
{
	struct object_request *newreq;
	struct walker_data *data = walker->data;

	newreq = xmalloc(sizeof(*newreq));
	newreq->walker = walker;
	hashcpy(newreq->sha1, sha1);
	newreq->repo = data->alt;
	newreq->state = WAITING;
	newreq->req = NULL;

	http_is_verbose = walker->get_verbosely;
	list_add_tail(&newreq->node, &object_queue_head);

#ifdef USE_CURL_MULTI
	fill_active_slots();
	step_active_slots();
#endif
}