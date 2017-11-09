void match_report(void)
{
	if (!DEBUG_GTE(DELTASUM, 1))
		return;

	rprintf(FINFO,
		"total: matches=%d  hash_hits=%d  false_alarms=%d data=%s\n",
		total_matches, total_hash_hits, total_false_alarms,
		big_num(stats.literal_data));
}