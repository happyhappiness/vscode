static int
process_station (int sk, const char *dev, struct ieee80211req_sta_info *si)
{
	struct iwreq iwr;
	static char mac[DATA_MAX_NAME_LEN];
	struct ieee80211req_sta_stats stats;
	const struct ieee80211_nodestats *ns = &stats.is_stats;
	int status;

	macaddr_to_str (mac, sizeof (mac), si->isi_macaddr);

	if (item_watched (STAT_NODE_TX_RATE))
		submit_gauge (dev, "node_tx_rate", mac, NULL,
			(si->isi_rates[si->isi_txrate] & IEEE80211_RATE_VAL) / 2);

	if (item_watched (STAT_NODE_RSSI))
		submit_gauge (dev, "node_rssi", mac, NULL, si->isi_rssi);

	memset (&iwr, 0, sizeof (iwr));
	sstrncpy(iwr.ifr_name, dev, sizeof (iwr.ifr_name));
	iwr.u.data.pointer = (void *) &stats;
	iwr.u.data.length = sizeof (stats);
	memcpy(stats.is_u.macaddr, si->isi_macaddr, IEEE80211_ADDR_LEN);
	status = ioctl(sk, IEEE80211_IOCTL_STA_STATS, &iwr);
	if (status < 0)
	{
		/* Silent, because not all interfaces support all ioctls. */
		DEBUG ("madwifi plugin: Sending IO-control "
				"IEEE80211_IOCTL_STA_STATS to device %s "
				"failed with status %i.",
				dev, status);
		return (status);
	}

	/* These two stats are handled as a special case as they are
	   a pair of 64bit values */
	if (item_watched (STAT_NODE_OCTETS))
		submit_counter2 (dev, "node_octets", mac, NULL,
			ns->ns_rx_bytes, ns->ns_tx_bytes);

	/* This stat is handled as a special case, because it is stored
	   as uin64_t, but we will ignore upper half */
	if (item_watched (STAT_NS_RX_BEACONS))
		submit_counter (dev, "node_stat", "ns_rx_beacons", mac,
			(ns->ns_rx_beacons & 0xFFFFFFFF));

	/* All other node statistics */
	process_stat_struct (NOD_STAT, ns, dev, mac, "node_stat", "ns_misc");
	return (0);
}