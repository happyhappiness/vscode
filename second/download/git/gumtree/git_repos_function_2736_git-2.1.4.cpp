static void collect_submodules_from_diff(struct diff_queue_struct *q,
					 struct diff_options *options,
					 void *data)
{
	int i;
	struct string_list *needs_pushing = data;

	for (i = 0; i < q->nr; i++) {
		struct diff_filepair *p = q->queue[i];
		if (!S_ISGITLINK(p->two->mode))
			continue;
		if (submodule_needs_pushing(p->two->path, p->two->sha1))
			string_list_insert(needs_pushing, p->two->path);
	}
}