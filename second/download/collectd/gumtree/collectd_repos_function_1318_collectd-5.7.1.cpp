static int tcsv_config_add_metric(oconfig_item_t *ci) {
  metric_definition_t *md;
  int status;

  md = calloc(1, sizeof(*md));
  if (md == NULL)
    return (-1);
  md->name = NULL;
  md->type = NULL;
  md->instance = NULL;
  md->data_source_type = -1;
  md->value_from = -1;
  md->next = NULL;

  status = cf_util_get_string(ci, &md->name);
  if (status != 0) {
    sfree(md);
    return (-1);
  }

  for (int i = 0; i < ci->children_num; ++i) {
    oconfig_item_t *option = ci->children + i;

    if (strcasecmp("Type", option->key) == 0)
      status = cf_util_get_string(option, &md->type);
    else if (strcasecmp("Instance", option->key) == 0)
      status = cf_util_get_string(option, &md->instance);
    else if (strcasecmp("ValueFrom", option->key) == 0)
      status = tcsv_config_get_index(option, &md->value_from);
    else {
      WARNING("tail_csv plugin: Option `%s' not allowed here.", option->key);
      status = -1;
    }

    if (status != 0)
      break;
  }

  if (status != 0) {
    tcsv_metric_definition_destroy(md);
    return (-1);
  }

  /* Verify all necessary options have been set. */
  if (md->type == NULL) {
    WARNING("tail_csv plugin: Option `Type' must be set.");
    status = -1;
  } else if (md->value_from < 0) {
    WARNING("tail_csv plugin: Option `ValueFrom' must be set.");
    status = -1;
  }
  if (status != 0) {
    tcsv_metric_definition_destroy(md);
    return (status);
  }

  if (metric_head == NULL)
    metric_head = md;
  else {
    metric_definition_t *last;
    last = metric_head;
    while (last->next != NULL)
      last = last->next;
    last->next = md;
  }

  return (0);
}