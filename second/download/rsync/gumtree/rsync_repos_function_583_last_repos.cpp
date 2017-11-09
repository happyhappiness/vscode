static void output_summary(void)
{
	if (INFO_GTE(STATS, 2)) {
		rprintf(FCLIENT, "\n");
		output_itemized_counts("Number of files", &stats.num_files);
		if (protocol_version >= 29)
			output_itemized_counts("Number of created files", &stats.created_files);
		if (protocol_version >= 31)
			output_itemized_counts("Number of deleted files", &stats.deleted_files);
		rprintf(FINFO,"Number of regular files transferred: %s\n",
			comma_num(stats.xferred_files));
		rprintf(FINFO,"Total file size: %s bytes\n",
			human_num(stats.total_size));
		rprintf(FINFO,"Total transferred file size: %s bytes\n",
			human_num(stats.total_transferred_size));
		rprintf(FINFO,"Literal data: %s bytes\n",
			human_num(stats.literal_data));
		rprintf(FINFO,"Matched data: %s bytes\n",
			human_num(stats.matched_data));
		rprintf(FINFO,"File list size: %s\n",
			human_num(stats.flist_size));
		if (stats.flist_buildtime) {
			rprintf(FINFO,
				"File list generation time: %s seconds\n",
				comma_dnum((double)stats.flist_buildtime / 1000, 3));
			rprintf(FINFO,
				"File list transfer time: %s seconds\n",
				comma_dnum((double)stats.flist_xfertime / 1000, 3));
		}
		rprintf(FINFO,"Total bytes sent: %s\n",
			human_num(total_written));
		rprintf(FINFO,"Total bytes received: %s\n",
			human_num(total_read));
	}

	if (INFO_GTE(STATS, 1)) {
		rprintf(FCLIENT, "\n");
		rprintf(FINFO,
			"sent %s bytes  received %s bytes  %s bytes/sec\n",
			human_num(total_written), human_num(total_read),
			human_dnum((total_written + total_read)/(0.5 + (endtime - starttime)), 2));
		rprintf(FINFO, "total size is %s  speedup is %s%s\n",
			human_num(stats.total_size),
			comma_dnum((double)stats.total_size / (total_written+total_read), 2),
			write_batch < 0 ? " (BATCH ONLY)" : dry_run ? " (DRY RUN)" : "");
	}

	fflush(stdout);
	fflush(stderr);
}