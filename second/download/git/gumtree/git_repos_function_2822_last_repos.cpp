const char *get_reflog_ident(struct reflog_walk_info *reflog_info)
{
	struct commit_reflog *commit_reflog = reflog_info->last_commit_reflog;
	struct reflog_info *info;

	if (!commit_reflog)
		return NULL;

	info = &commit_reflog->reflogs->items[commit_reflog->recno+1];
	return info->email;
}