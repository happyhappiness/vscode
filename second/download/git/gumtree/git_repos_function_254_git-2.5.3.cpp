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
			if (walker->fetch(walker, obj->sha1)) {
				report_missing(obj);
				return -1;
			}
		}
		if (!obj->type)
			parse_object(obj->sha1);
		if (process_object(walker, obj))
			return -1;
	}
	return 0;
}