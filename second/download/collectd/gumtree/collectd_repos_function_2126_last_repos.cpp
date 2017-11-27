static int udb_result_create(const char *query_name, /* {{{ */
                             udb_result_t **r_head, oconfig_item_t *ci) {
  udb_result_t *r;
  int status;

  if (ci->values_num != 0) {
    WARNING("db query utils: The `Result' block doesn't accept "
            "any arguments. Ignoring %i argument%s.",
            ci->values_num, (ci->values_num == 1) ? "" : "s");
  }

  r = calloc(1, sizeof(*r));
  if (r == NULL) {
    ERROR("db query utils: calloc failed.");
    return -1;
  }
  r->type = NULL;
  r->instance_prefix = NULL;
  r->instances = NULL;
  r->values = NULL;
  r->metadata = NULL;
  r->next = NULL;

  /* Fill the `udb_result_t' structure.. */
  status = 0;
  for (int i = 0; i < ci->children_num; i++) {
    oconfig_item_t *child = ci->children + i;

    if (strcasecmp("Type", child->key) == 0)
      status = udb_config_set_string(&r->type, child);
    else if (strcasecmp("InstancePrefix", child->key) == 0)
      status = udb_config_set_string(&r->instance_prefix, child);
    else if (strcasecmp("InstancesFrom", child->key) == 0)
      status = udb_config_add_string(&r->instances, &r->instances_num, child);
    else if (strcasecmp("ValuesFrom", child->key) == 0)
      status = udb_config_add_string(&r->values, &r->values_num, child);
    else if (strcasecmp("MetadataFrom", child->key) == 0)
      status = udb_config_add_string(&r->metadata, &r->metadata_num, child);
    else {
      WARNING("db query utils: Query `%s': Option `%s' not allowed here.",
              query_name, child->key);
      status = -1;
    }

    if (status != 0)
      break;
  }

  /* Check that all necessary options have been given. */
  while (status == 0) {
    if (r->type == NULL) {
      WARNING("db query utils: `Type' not given for "
              "result in query `%s'",
              query_name);
      status = -1;
    }
    if (r->values == NULL) {
      WARNING("db query utils: `ValuesFrom' not given for "
              "result in query `%s'",
              query_name);
      status = -1;
    }

    break;
  } /* while (status == 0) */

  if (status != 0) {
    udb_result_free(r);
    return -1;
  }

  /* If all went well, add this result to the list of results. */
  if (*r_head == NULL) {
    *r_head = r;
  } else {
    udb_result_t *last;

    last = *r_head;
    while (last->next != NULL)
      last = last->next;

    last->next = r;
  }

  return 0;
}