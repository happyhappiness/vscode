static int dns_config(const char *key, const char *value) {
  if (strcasecmp(key, "Interface") == 0) {
    if (pcap_device != NULL)
      free(pcap_device);
    if ((pcap_device = strdup(value)) == NULL)
      return (1);
  } else if (strcasecmp(key, "IgnoreSource") == 0) {
    if (value != NULL)
      ignore_list_add_name(value);
  } else if (strcasecmp(key, "SelectNumericQueryTypes") == 0) {
    if ((value != NULL) && IS_FALSE(value))
      select_numeric_qtype = 0;
    else
      select_numeric_qtype = 1;
  } else {
    return (-1);
  }

  return (0);
}