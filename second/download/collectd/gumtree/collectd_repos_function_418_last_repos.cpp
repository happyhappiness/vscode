static int nut_config(const char *key, const char *value) {
  if (strcasecmp(key, "UPS") == 0)
    return nut_add_ups(value);
  else if (strcasecmp(key, "FORCESSL") == 0)
    return nut_force_ssl(value);
  else if (strcasecmp(key, "VERIFYPEER") == 0)
    return nut_verify_peer(value);
  else if (strcasecmp(key, "CAPATH") == 0)
    return nut_ca_path(value);
  else if (strcasecmp(key, "CONNECTTIMEOUT") == 0)
    return nut_set_connect_timeout(value);
  else
    return -1;
}