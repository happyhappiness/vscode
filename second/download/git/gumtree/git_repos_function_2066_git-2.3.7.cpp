void get_reflog_message(struct strbuf *sb,
			struct reflog_walk_info *reflog_info)
{
	struct commit_reflog *commit_reflog = reflog_info->last_commit_reflog;
	struct reflog_info *info;
	size_t len;

	if (!commit_reflog)
		return;

	info = &commit_reflog->reflogs->items[commit_reflog->recno+1];
	len = strlen(info->message);
	if (len > 0)
		len--; /* strip away trailing newline */
	strbuf_add(sb, info->message, len);
}