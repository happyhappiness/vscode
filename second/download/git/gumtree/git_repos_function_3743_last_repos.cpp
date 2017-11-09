static void collect_changed_submodules_cb(struct diff_queue_struct *q,
					  struct diff_options *options,
					  void *data)
{
	int i;
	struct string_list *changed = data;

	for (i = 0; i < q->nr; i++) {
		struct diff_filepair *p = q->queue[i];
		struct oid_array *commits;
		if (!S_ISGITLINK(p->two->mode))
			continue;

		if (S_ISGITLINK(p->one->mode)) {
			/*
			 * NEEDSWORK: We should honor the name configured in
			 * the .gitmodules file of the commit we are examining
			 * here to be able to correctly follow submodules
			 * being moved around.
			 */
			commits = submodule_commits(changed, p->two->path);
			oid_array_append(commits, &p->two->oid);
		} else {
			/* Submodule is new or was moved here */
			/*
			 * NEEDSWORK: When the .git directories of submodules
			 * live inside the superprojects .git directory some
			 * day we should fetch new submodules directly into
			 * that location too when config or options request
			 * that so they can be checked out from there.
			 */
			continue;
		}
	}
}