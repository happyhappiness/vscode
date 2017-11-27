static iface_counter ovs_stats_counter_name_to_type(const char *counter) {
  iface_counter index = not_supported;

  if (counter == NULL)
    return not_supported;

  for (int i = 0; i < IFACE_COUNTER_COUNT; i++) {
    if (strncmp(iface_counter_table[i], counter,
                strlen(iface_counter_table[i])) == 0) {
      index = i;
      break;
    }
  }
  return index;
}