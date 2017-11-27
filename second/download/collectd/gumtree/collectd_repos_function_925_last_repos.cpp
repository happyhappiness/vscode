static int powerdns_read_server(list_item_t *item) /* {{{ */
{
  char *buffer = NULL;
  size_t buffer_size = 0;
  int status;

  char *dummy;
  char *saveptr;

  char *key;
  char *value;

  const char *const *fields;
  int fields_num;

  if (item->command == NULL)
    item->command = strdup(SERVER_COMMAND);
  if (item->command == NULL) {
    ERROR("powerdns plugin: strdup failed.");
    return -1;
  }

  status = powerdns_get_data(item, &buffer, &buffer_size);
  if (status != 0)
    return -1;

  if (item->fields_num != 0) {
    fields = (const char *const *)item->fields;
    fields_num = item->fields_num;
  } else {
    fields = default_server_fields;
    fields_num = default_server_fields_num;
  }

  assert(fields != NULL);
  assert(fields_num > 0);

  /* corrupt-packets=0,deferred-cache-inserts=0,deferred-cache-lookup=0,latency=0,packetcache-hit=0,packetcache-miss=0,packetcache-size=0,qsize-q=0,query-cache-hit=0,query-cache-miss=0,recursing-answers=0,recursing-questions=0,servfail-packets=0,tcp-answers=0,tcp-queries=0,timedout-packets=0,udp-answers=0,udp-queries=0,udp4-answers=0,udp4-queries=0,udp6-answers=0,udp6-queries=0,
   */
  dummy = buffer;
  saveptr = NULL;
  while ((key = strtok_r(dummy, ",", &saveptr)) != NULL) {
    dummy = NULL;

    value = strchr(key, '=');
    if (value == NULL)
      break;

    *value = '\0';
    value++;

    if (value[0] == '\0')
      continue;

    /* Check if this item was requested. */
    int i;
    for (i = 0; i < fields_num; i++)
      if (strcasecmp(key, fields[i]) == 0)
        break;
    if (i >= fields_num)
      continue;

    submit(item->instance, key, value);
  } /* while (strtok_r) */

  sfree(buffer);

  return 0;
}