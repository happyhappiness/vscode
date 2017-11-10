static void prefetch(struct walker *walker, unsigned char *sha1)
{
	struct object_request *newreq;
	struct object_request *tail;
	struct walker_data *data = walker->data;

	newreq = xmalloc(sizeof(*newreq));
	newreq->walker = walker;
	hashcpy(newreq->sha1, sha1);
	newreq->repo = data->alt;
	newreq->state = WAITING;
	newreq->req = NULL;
	newreq->next = NULL;

	http_is_verbose = walker->get_verbosely;

	if (object_queue_head == NULL) {
		object_queue_head = newreq;
	} else {
		tail = object_queue_head;
		while (tail->next != NULL)
			tail = tail->next;
		tail->next = newreq;
	}

#ifdef USE_CURL_MULTI
	fill_active_slots();
	step_active_slots();
#endif
}