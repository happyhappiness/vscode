static unsigned int parse_ex_stats_flags(char **exstats, int numexstats) {
  unsigned int ex_stats_flags = ex_stats_none;
  for (int i = 0; i < numexstats; i++) {
    for (int j = 0; ex_stats_table[j].name != NULL; j++) {
      if (strcasecmp(exstats[i], ex_stats_table[j].name) == 0) {
        DEBUG(PLUGIN_NAME " plugin: enabling extra stats for '%s'",
              ex_stats_table[j].name);
        ex_stats_flags |= ex_stats_table[j].flag;
        break;
      }

      if (ex_stats_table[j + 1].name == NULL) {
        ERROR(PLUGIN_NAME ": Unmatched ExtraStats option: %s", exstats[i]);
      }
    }
  }
  return ex_stats_flags;
}