static void cipvs_submit_service(struct ip_vs_service_entry *se) {
  struct ip_vs_stats_user stats = se->stats;
  struct ip_vs_get_dests *dests = ipvs_get_dests(se);

  char pi[DATA_MAX_NAME_LEN];

  if (0 != get_pi(se, pi, sizeof(pi))) {
    free(dests);
    return;
  }

  cipvs_submit_connections(pi, NULL, stats.conns);
  cipvs_submit_if(pi, "if_packets", NULL, stats.inpkts, stats.outpkts);
  cipvs_submit_if(pi, "if_octets", NULL, stats.inbytes, stats.outbytes);

  for (size_t i = 0; i < dests->num_dests; ++i)
    cipvs_submit_dest(pi, &dests->entrytable[i]);

  free(dests);
  return;
}