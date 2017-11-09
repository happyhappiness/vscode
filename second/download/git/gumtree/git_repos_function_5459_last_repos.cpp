static void update_callback(struct diff_queue_struct *q,
			    struct diff_options *opt, void *cbdata)
{
	int i;
	struct update_callback_data *data = cbdata;

	for (i = 0; i < q->nr; i++) {
		struct diff_filepair *p = q->queue[i];
		const char *path = p->one->path;
		switch (fix_unmerged_status(p, data)) {
		default:
			die(_("unexpected diff status %c"), p->status);
		case DIFF_STATUS_MODIFIED:
		case DIFF_STATUS_TYPE_CHANGED:
			if (add_file_to_index(&the_index, path,	data->flags)) {
				if (!(data->flags & ADD_CACHE_IGNORE_ERRORS))
					die(_("updating files failed"));
				data->add_errors++;
			}
			break;
		case DIFF_STATUS_DELETED:
			if (data->flags & ADD_CACHE_IGNORE_REMOVAL)
				break;
			if (!(data->flags & ADD_CACHE_PRETEND))
				remove_file_from_index(&the_index, path);
			if (data->flags & (ADD_CACHE_PRETEND|ADD_CACHE_VERBOSE))
				printf(_("remove '%s'\n"), path);
			break;
		}
	}
}