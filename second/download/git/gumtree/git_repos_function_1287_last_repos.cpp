static timestamp_t comparison_date(const struct rev_info *revs,
				   struct commit *commit)
{
	return revs->reflog_info ?
		get_reflog_timestamp(revs->reflog_info) :
		commit->date;
}