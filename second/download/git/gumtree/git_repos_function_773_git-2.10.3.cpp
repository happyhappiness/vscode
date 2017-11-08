int compare_commits_by_commit_date(const void *a_, const void *b_, void *unused)
{
	const struct commit *a = a_, *b = b_;
	/* newer commits with larger date first */
	if (a->date < b->date)
		return 1;
	else if (a->date > b->date)
		return -1;
	return 0;
}