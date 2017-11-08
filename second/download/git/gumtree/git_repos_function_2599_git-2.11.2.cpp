void show_reflog_message(struct reflog_walk_info *reflog_info, int oneline,
			 const struct date_mode *dmode, int force_date)
{
	if (reflog_info && reflog_info->last_commit_reflog) {
		struct commit_reflog *commit_reflog = reflog_info->last_commit_reflog;
		struct reflog_info *info;
		struct strbuf selector = STRBUF_INIT;

		info = &commit_reflog->reflogs->items[commit_reflog->recno+1];
		get_reflog_selector(&selector, reflog_info, dmode, force_date, 0);
		if (oneline) {
			printf("%s: %s", selector.buf, info->message);
		}
		else {
			printf("Reflog: %s (%s)\nReflog message: %s",
			       selector.buf, info->email, info->message);
		}

		strbuf_release(&selector);
	}
}