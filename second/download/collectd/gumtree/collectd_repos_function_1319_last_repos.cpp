static int mv_create(const oconfig_item_t *ci, void **user_data) /* {{{ */
{
  mv_match_t *m;
  int status;

  m = calloc(1, sizeof(*m));
  if (m == NULL) {
    ERROR("mv_create: calloc failed.");
    return -ENOMEM;
  }

  m->min = NAN;
  m->max = NAN;
  m->invert = 0;
  m->satisfy = SATISFY_ALL;
  m->data_sources = NULL;
  m->data_sources_num = 0;

  status = 0;
  for (int i = 0; i < ci->children_num; i++) {
    oconfig_item_t *child = ci->children + i;

    if (strcasecmp("Min", child->key) == 0)
      status = mv_config_add_gauge(&m->min, child);
    else if (strcasecmp("Max", child->key) == 0)
      status = mv_config_add_gauge(&m->max, child);
    else if (strcasecmp("Invert", child->key) == 0)
      status = mv_config_add_boolean(&m->invert, child);
    else if (strcasecmp("Satisfy", child->key) == 0)
      status = mv_config_add_satisfy(m, child);
    else if (strcasecmp("DataSource", child->key) == 0)
      status = mv_config_add_data_source(m, child);
    else {
      ERROR("`value' match: The `%s' configuration option is not "
            "understood and will be ignored.",
            child->key);
      status = 0;
    }

    if (status != 0)
      break;
  }

  /* Additional sanity-checking */
  while (status == 0) {
    if (isnan(m->min) && isnan(m->max)) {
      ERROR("`value' match: Neither minimum nor maximum are defined. "
            "This match will be ignored.");
      status = -1;
    }

    break;
  }

  if (status != 0) {
    mv_free_match(m);
    return status;
  }

  *user_data = m;
  return 0;
}