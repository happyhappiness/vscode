static int traverse_reachable(void)
{
	struct progress *progress = NULL;
	unsigned int nr = 0;
	int result = 0;
	if (show_progress)
		progress = start_progress_delay(_("Checking connectivity"), 0, 0, 2);
	while (pending.nr) {
		struct object_array_entry *entry;
		struct object *obj;

		entry = pending.objects + --pending.nr;
		obj = entry->item;
		result |= traverse_one_object(obj);
		display_progress(progress, ++nr);
	}
	stop_progress(&progress);
	return !!result;
}