static int mt_create(const oconfig_item_t *ci, void **user_data) /* {{{ */
{
  mt_match_t *m;
  int status;

  m = calloc(1, sizeof(*m));
  if (m == NULL) {
    ERROR("mt_create: calloc failed.");
    return -ENOMEM;
  }

  m->future = 0;
  m->past = 0;

  status = 0;
  for (int i = 0; i < ci->children_num; i++) {
    oconfig_item_t *child = ci->children + i;

    if (strcasecmp("Future", child->key) == 0)
      status = cf_util_get_cdtime(child, &m->future);
    else if (strcasecmp("Past", child->key) == 0)
      status = cf_util_get_cdtime(child, &m->past);
    else {
      ERROR("timediff match: The `%s' configuration option is not "
            "understood and will be ignored.",
            child->key);
      status = 0;
    }

    if (status != 0)
      break;
  }

  /* Additional sanity-checking */
  while (status == 0) {
    if ((m->future == 0) && (m->past == 0)) {
      ERROR("timediff match: Either `Future' or `Past' must be configured. "
            "This match will be ignored.");
      status = -1;
    }

    break;
  }

  if (status != 0) {
    free(m);
    return status;
  }

  *user_data = m;
  return 0;
}