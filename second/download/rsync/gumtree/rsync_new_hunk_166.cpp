
void match_report(void)
{
  if (verbose <= 1)
    return;

  fprintf(FINFO,
	  "total: matches=%d  tag_hits=%d  false_alarms=%d  data=%d\n",
	  total_matches,total_tag_hits,
	  total_false_alarms,total_data_transfer);
}
