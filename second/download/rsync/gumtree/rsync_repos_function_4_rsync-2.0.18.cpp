void match_sums(int f,struct sum_struct *s,struct map_struct *buf,OFF_T len)
{
	char file_sum[MD4_SUM_LENGTH];

	last_match = 0;
	false_alarms = 0;
	tag_hits = 0;
	matches=0;
	data_transfer=0;

	sum_init();

	if (len > 0 && s->count>0) {
		build_hash_table(s);
		
		if (verbose > 2) 
			rprintf(FINFO,"built hash table\n");
		
		hash_search(f,s,buf,len);
		
		if (verbose > 2) 
			rprintf(FINFO,"done hash search\n");
	} else {
		matched(f,s,buf,len,-1);
	}

	sum_end(file_sum);

	if (remote_version >= 14) {
		if (verbose > 2)
			rprintf(FINFO,"sending file_sum\n");
		write_buf(f,file_sum,MD4_SUM_LENGTH);
	}

	if (targets) {
		free(targets);
		targets=NULL;
	}
	
	if (verbose > 2)
		rprintf(FINFO, "false_alarms=%d tag_hits=%d matches=%d\n",
			false_alarms, tag_hits, matches);
	
	total_tag_hits += tag_hits;
	total_false_alarms += false_alarms;
	total_matches += matches;
	stats.literal_data += data_transfer;
}