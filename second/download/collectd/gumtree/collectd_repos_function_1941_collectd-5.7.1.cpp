static inline void macaddr_to_str(char *buf, size_t bufsize,
                                  const uint8_t mac[IEEE80211_ADDR_LEN]) {
  ssnprintf(buf, bufsize, "%02x:%02x:%02x:%02x:%02x:%02x", mac[0], mac[1],
            mac[2], mac[3], mac[4], mac[5]);
}