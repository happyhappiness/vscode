static void cipvs_submit_dest (char *pi, struct ip_vs_dest_entry *de) {
	struct ip_vs_stats_user stats = de->stats;

	char ti[DATA_MAX_NAME_LEN];

	if (0 != get_ti (de, ti, sizeof (ti)))
		return;

	cipvs_submit_connections (pi, ti, stats.conns);
	cipvs_submit_if (pi, "if_packets", ti, stats.inpkts, stats.outpkts);
	cipvs_submit_if (pi, "if_octets", ti, stats.inbytes, stats.outbytes);
	return;
}