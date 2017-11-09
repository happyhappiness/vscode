static int loop(struct walker *walker)
{
	struct object_list *elem;

	while (process_queue) {
		struct object *obj = process_queue->item;
		elem = process_queue;
		process_queue = elem->next;
		free(elem);
		if (!process_queue)
			process_queue_end = &process_queue;

		/* If we are not scanning this object, we placed it in
		 * the queue because we needed to fetch it first.
		 */
		if (! (obj->flags & TO_SCAN)) {
			if (walker->fetch(walker, obj->oid.hash)) {
				report_missing(obj);
				return -1;
			}
		}
		if (!obj->type)
			parse_object(&obj->oid);
		if (process_object(walker, obj))
			return -1;
	}
	return 0;
}