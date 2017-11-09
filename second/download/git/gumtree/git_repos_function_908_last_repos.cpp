static int compare_commits_by_author_date(const void *a_, const void *b_,
					  void *cb_data)
{
	const struct commit *a = a_, *b = b_;
	struct author_date_slab *author_date = cb_data;
	timestamp_t a_date = *(author_date_slab_at(author_date, a));
	timestamp_t b_date = *(author_date_slab_at(author_date, b));

	/* newer commits with larger date first */
	if (a_date < b_date)
		return 1;
	else if (a_date > b_date)
		return -1;
	return 0;
}