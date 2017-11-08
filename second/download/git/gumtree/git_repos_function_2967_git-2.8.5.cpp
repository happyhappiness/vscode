static void do_rerere_one_path(struct string_list_item *rr_item,
			       struct string_list *update)
{
	const char *path = rr_item->string;
	const struct rerere_id *id = rr_item->util;

	/* Is there a recorded resolution we could attempt to apply? */
	if (has_rerere_resolution(id)) {
		if (merge(id, path))
			return; /* failed to replay */

		if (rerere_autoupdate)
			string_list_insert(update, path);
		else
			fprintf(stderr,
				"Resolved '%s' using previous resolution.\n",
				path);
	} else if (!handle_file(path, NULL, NULL)) {
		/* The user has resolved it. */
		copy_file(rerere_path(id, "postimage"), path, 0666);
		fprintf(stderr, "Recorded resolution for '%s'.\n", path);
	} else {
		return;
	}
	free_rerere_id(rr_item);
	rr_item->util = NULL;
}