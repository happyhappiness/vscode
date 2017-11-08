void match_report(void)
{
	if (verbose <= 1)
		return;

	rprintf(FINFO,
		"total: matches=%d  tag_hits=%d  false_alarms=%d data=%.0f\n",
		total_matches,total_tag_hits,
		total_false_alarms,
		(double)stats.literal_data);
}