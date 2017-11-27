static int openvpn_init(void) {
  if (!collect_individual_users && !collect_compression &&
      !collect_user_count) {
    WARNING("OpenVPN plugin: Neither `CollectIndividualUsers', "
            "`CollectCompression', nor `CollectUserCount' is true. There's no "
            "data left to collect.");
    return (-1);
  }

  plugin_register_read("openvpn", openvpn_read);
  plugin_register_shutdown("openvpn", openvpn_shutdown);

  return (0);
}