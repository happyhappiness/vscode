int add_reflog_for_walk(struct reflog_walk_info *info,
		struct commit *commit, const char *name)
{
	timestamp_t timestamp = 0;
	int recno = -1;
	struct string_list_item *item;
	struct complete_reflogs *reflogs;
	char *branch, *at = strchr(name, '@');
	struct commit_reflog *commit_reflog;
	enum selector_type selector = SELECTOR_NONE;

	if (commit->object.flags & UNINTERESTING)
		die ("Cannot walk reflogs for %s", name);

	branch = xstrdup(name);
	if (at && at[1] == '{') {
		char *ep;
		branch[at - name] = '\0';
		recno = strtoul(at + 2, &ep, 10);
		if (*ep != '}') {
			recno = -1;
			timestamp = approxidate(at + 2);
			selector = SELECTOR_DATE;
		}
		else
			selector = SELECTOR_INDEX;
	} else
		recno = 0;

	item = string_list_lookup(&info->complete_reflogs, branch);
	if (item)
		reflogs = item->util;
	else {
		if (*branch == '\0') {
			struct object_id oid;
			free(branch);
			branch = resolve_refdup("HEAD", 0, oid.hash, NULL);
			if (!branch)
				die ("No current branch");

		}
		reflogs = read_complete_reflog(branch);
		if (!reflogs || reflogs->nr == 0) {
			struct object_id oid;
			char *b;
			int ret = dwim_log(branch, strlen(branch),
					   oid.hash, &b);
			if (ret > 1)
				free(b);
			else if (ret == 1) {
				free_complete_reflog(reflogs);
				free(branch);
				branch = b;
				reflogs = read_complete_reflog(branch);
			}
		}
		if (!reflogs || reflogs->nr == 0) {
			free_complete_reflog(reflogs);
			free(branch);
			return -1;
		}
		string_list_insert(&info->complete_reflogs, branch)->util
			= reflogs;
	}
	free(branch);

	commit_reflog = xcalloc(1, sizeof(struct commit_reflog));
	if (recno < 0) {
		commit_reflog->recno = get_reflog_recno_by_time(reflogs, timestamp);
		if (commit_reflog->recno < 0) {
			free(commit_reflog);
			return -1;
		}
	} else
		commit_reflog->recno = reflogs->nr - recno - 1;
	commit_reflog->selector = selector;
	commit_reflog->reflogs = reflogs;

	ALLOC_GROW(info->logs, info->nr + 1, info->alloc);
	info->logs[info->nr++] = commit_reflog;

	return 0;
}