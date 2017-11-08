static int is_racy_stat(const struct index_state *istate,
			const struct stat_data *sd)
{
	return (istate->timestamp.sec &&
#ifdef USE_NSEC
		 /* nanosecond timestamped files can also be racy! */
		(istate->timestamp.sec < sd->sd_mtime.sec ||
		 (istate->timestamp.sec == sd->sd_mtime.sec &&
		  istate->timestamp.nsec <= sd->sd_mtime.nsec))
#else
		istate->timestamp.sec <= sd->sd_mtime.sec
#endif
		);
}