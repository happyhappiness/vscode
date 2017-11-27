static int process_80211stats(int sk, const char *dev) {
  struct ifreq ifr;
  struct ieee80211_stats stats;
  int status;

  sstrncpy(ifr.ifr_name, dev, sizeof(ifr.ifr_name));
  ifr.ifr_data = (void *)&stats;
  status = ioctl(sk, SIOCG80211STATS, &ifr);
  if (status < 0) {
    /* Silent, because not all interfaces support all ioctls. */
    DEBUG("madwifi plugin: Sending IO-control "
          "SIOCG80211STATS to device %s "
          "failed with status %i.",
          dev, status);
    return (status);
  }

  process_stat_struct(IFA_STAT, &stats, dev, NULL, "ath_stat", "is_misc");
  return (0);
}