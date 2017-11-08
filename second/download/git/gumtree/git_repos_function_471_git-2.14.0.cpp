static int compare_commits_by_reverse_commit_date(const void *a,
						  const void *b,
						  void *c)
{
	return -compare_commits_by_commit_date(a, b, c);
}