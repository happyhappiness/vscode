			revs->count_right++;
		finish_commit(commit, data);
		return;
	}

	if (info->show_timestamp)
		printf("%"PRItime" ", commit->date);
	if (info->header_prefix)
		fputs(info->header_prefix, stdout);

	if (!revs->graph)
		fputs(get_revision_mark(revs, commit), stdout);
	if (revs->abbrev_commit && revs->abbrev)
