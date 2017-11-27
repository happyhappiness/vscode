static int openvpn_init(void) {
  if (!collect_individual_users && !collect_compression &&
      !collect_user_count) {
    WARNING("OpenVPN plugin: Neither `CollectIndividualUsers', "
            "`CollectCompression', nor `CollectUserCount' is true. There's no "
            "data left to collect.");
    return -1;
  }

  return 0;
}