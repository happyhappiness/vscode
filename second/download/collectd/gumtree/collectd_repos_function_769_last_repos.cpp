static int redis_db_stats(char *node, char const *info_line) /* {{{ */
{
  /* redis_db_stats parses and dispatches Redis database statistics,
   * currently the number of keys for each database.
   * info_line needs to have the following format:
   *   db0:keys=4,expires=0,avg_ttl=0
   */

  for (int db = 0; db < REDIS_DEF_DB_COUNT; db++) {
    static char buf[MAX_REDIS_VAL_SIZE];
    static char field_name[11];
    static char db_id[3];
    value_t val;
    char *str;
    int i;

    snprintf(field_name, sizeof(field_name), "db%d:keys=", db);

    str = strstr(info_line, field_name);
    if (!str)
      continue;

    str += strlen(field_name);
    for (i = 0; (*str && isdigit((int)*str)); i++, str++)
      buf[i] = *str;
    buf[i] = '\0';

    if (parse_value(buf, &val, DS_TYPE_GAUGE) != 0) {
      WARNING("redis plugin: Unable to parse field `%s'.", field_name);
      return -1;
    }

    snprintf(db_id, sizeof(db_id), "%d", db);
    redis_submit(node, "records", db_id, val);
  }
  return 0;

}