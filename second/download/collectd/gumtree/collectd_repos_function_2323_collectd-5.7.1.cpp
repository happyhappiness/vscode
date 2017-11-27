static int conntrack_read(void) {
  value_t conntrack, conntrack_max, conntrack_pct;

  char const *path = old_files ? CONNTRACK_FILE_OLD : CONNTRACK_FILE;
  if (parse_value_file(path, &conntrack, DS_TYPE_GAUGE) != 0) {
    ERROR("conntrack plugin: Reading \"%s\" failed.", path);
    return (-1);
  }

  path = old_files ? CONNTRACK_MAX_FILE_OLD : CONNTRACK_MAX_FILE;
  if (parse_value_file(path, &conntrack_max, DS_TYPE_GAUGE) != 0) {
    ERROR("conntrack plugin: Reading \"%s\" failed.", path);
    return (-1);
  }

  conntrack_pct.gauge = (conntrack.gauge / conntrack_max.gauge) * 100;

  conntrack_submit("conntrack", NULL, conntrack);
  conntrack_submit("conntrack", "max", conntrack_max);
  conntrack_submit("percent", "used", conntrack_pct);

  return (0);
}