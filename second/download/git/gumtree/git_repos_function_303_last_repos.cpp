static int process(struct walker *walker, struct object *obj)
{
	if (obj->flags & SEEN)
		return 0;
	obj->flags |= SEEN;

	if (has_object_file(&obj->oid)) {
		/* We already have it, so we should scan it now. */
		obj->flags |= TO_SCAN;
	}
	else {
		if (obj->flags & COMPLETE)
			return 0;
		walker->prefetch(walker, obj->oid.hash);
	}

	object_list_insert(obj, process_queue_end);
	process_queue_end = &(*process_queue_end)->next;
	return 0;
}