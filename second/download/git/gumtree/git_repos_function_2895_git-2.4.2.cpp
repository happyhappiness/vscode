static void submodule_collect_changed_cb(struct diff_queue_struct *q,
					 struct diff_options *options,
					 void *data)
{
	int i;
	for (i = 0; i < q->nr; i++) {
		struct diff_filepair *p = q->queue[i];
		if (!S_ISGITLINK(p->two->mode))
			continue;

		if (S_ISGITLINK(p->one->mode)) {
			/* NEEDSWORK: We should honor the name configured in
			 * the .gitmodules file of the commit we are examining
			 * here to be able to correctly follow submodules
			 * being moved around. */
			struct string_list_item *path;
			path = unsorted_string_list_lookup(&changed_submodule_paths, p->two->path);
			if (!path && !is_submodule_commit_present(p->two->path, p->two->sha1))
				string_list_append(&changed_submodule_paths, xstrdup(p->two->path));
		} else {
			/* Submodule is new or was moved here */
			/* NEEDSWORK: When the .git directories of submodules
			 * live inside the superprojects .git directory some
			 * day we should fetch new submodules directly into
			 * that location too when config or options request
			 * that so they can be checked out from there. */
			continue;
		}
	}
}