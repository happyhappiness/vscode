
void match_report(void)
{
	if (verbose <= 1)
		return;

	fprintf(FINFO,
		"total: matches=%d  tag_hits=%d  false_alarms=%d  data=%ld\n",
		total_matches,total_tag_hits,
		total_false_alarms,(long)total_data_transfer);
}
