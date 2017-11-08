static void collect_submodules_from_diff(struct diff_queue_struct *q,
					 struct diff_options *options,
					 void *data)
{
	int i;
	struct string_list *submodules = data;

	for (i = 0; i < q->nr; i++) {
		struct diff_filepair *p = q->queue[i];
		struct oid_array *commits;
		if (!S_ISGITLINK(p->two->mode))
			continue;
		commits = submodule_commits(submodules, p->two->path);
		oid_array_append(commits, &p->two->oid);
	}
}