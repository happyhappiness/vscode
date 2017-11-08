void get_reflog_selector(struct strbuf *sb,
			 struct reflog_walk_info *reflog_info,
			 enum date_mode dmode, int force_date,
			 int shorten)
{
	struct commit_reflog *commit_reflog = reflog_info->last_commit_reflog;
	struct reflog_info *info;
	const char *printed_ref;

	if (!commit_reflog)
		return;

	if (shorten) {
		if (!commit_reflog->reflogs->short_ref)
			commit_reflog->reflogs->short_ref
				= shorten_unambiguous_ref(commit_reflog->reflogs->ref, 0);
		printed_ref = commit_reflog->reflogs->short_ref;
	} else {
		printed_ref = commit_reflog->reflogs->ref;
	}

	strbuf_addf(sb, "%s@{", printed_ref);
	if (commit_reflog->selector == SELECTOR_DATE ||
	    (commit_reflog->selector == SELECTOR_NONE && force_date)) {
		info = &commit_reflog->reflogs->items[commit_reflog->recno+1];
		strbuf_addstr(sb, show_date(info->timestamp, info->tz, dmode));
	} else {
		strbuf_addf(sb, "%d", commit_reflog->reflogs->nr
			    - 2 - commit_reflog->recno);
	}

	strbuf_addch(sb, '}');
}