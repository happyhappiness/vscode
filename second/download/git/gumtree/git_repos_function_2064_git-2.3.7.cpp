void fake_reflog_parent(struct reflog_walk_info *info, struct commit *commit)
{
	struct commit_info *commit_info =
		get_commit_info(commit, &info->reflogs, 0);
	struct commit_reflog *commit_reflog;
	struct reflog_info *reflog;

	info->last_commit_reflog = NULL;
	if (!commit_info)
		return;

	commit_reflog = commit_info->util;
	if (commit_reflog->recno < 0) {
		commit->parents = NULL;
		return;
	}

	reflog = &commit_reflog->reflogs->items[commit_reflog->recno];
	info->last_commit_reflog = commit_reflog;
	commit_reflog->recno--;
	commit_info->commit = (struct commit *)parse_object(reflog->osha1);
	if (!commit_info->commit) {
		commit->parents = NULL;
		return;
	}

	commit->parents = xcalloc(1, sizeof(struct commit_list));
	commit->parents->item = commit_info->commit;
}