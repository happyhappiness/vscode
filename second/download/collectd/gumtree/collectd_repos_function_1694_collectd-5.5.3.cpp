static int
process_athstats (int sk, const char *dev)
{
	struct ifreq ifr;
	struct ath_stats stats;
	int status;

	sstrncpy (ifr.ifr_name, dev, sizeof (ifr.ifr_name));
	ifr.ifr_data = (void *) &stats;
	status = ioctl (sk, SIOCGATHSTATS, &ifr);
	if (status < 0)
	{
		/* Silent, because not all interfaces support all ioctls. */
		DEBUG ("madwifi plugin: Sending IO-control "
				"SIOCGATHSTATS to device %s "
				"failed with status %i.",
				dev, status);
		return (status);
	}

	/* These stats are handled as a special case, because they are
	   eight values each */

	if (item_watched (STAT_AST_ANT_RX))
		submit_antx (dev, "ast_ant_rx", stats.ast_ant_rx,
				STATIC_ARRAY_SIZE (stats.ast_ant_rx));

	if (item_watched (STAT_AST_ANT_TX))
		submit_antx (dev, "ast_ant_tx", stats.ast_ant_tx,
				STATIC_ARRAY_SIZE (stats.ast_ant_tx));

	/* All other ath statistics */
	process_stat_struct (ATH_STAT, &stats, dev, NULL, "ath_stat", "ast_misc");
	return (0);
}