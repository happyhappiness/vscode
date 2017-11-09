timestamp_t get_reflog_timestamp(struct reflog_walk_info *reflog_info)
{
	struct commit_reflog *commit_reflog = reflog_info->last_commit_reflog;
	struct reflog_info *info;

	if (!commit_reflog)
		return 0;

	info = &commit_reflog->reflogs->items[commit_reflog->recno+1];
	return info->timestamp;
}