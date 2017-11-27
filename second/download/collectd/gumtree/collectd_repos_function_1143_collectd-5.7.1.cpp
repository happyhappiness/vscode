static data_volume_usage_t *get_volume_usage(cfg_volume_usage_t *cvu, /* {{{ */
                                             const char *name) {
  data_volume_usage_t *last;
  data_volume_usage_t *new;

  int ignore_capacity = 0;
  int ignore_snapshot = 0;

  if ((cvu == NULL) || (name == NULL))
    return (NULL);

  last = cvu->volumes;
  while (last != NULL) {
    if (strcmp(last->name, name) == 0)
      return (last);

    if (last->next == NULL)
      break;

    last = last->next;
  }

  /* Check the ignorelists. If *both* tell us to ignore a volume, return NULL.
   */
  ignore_capacity = ignorelist_match(cvu->il_capacity, name);
  ignore_snapshot = ignorelist_match(cvu->il_snapshot, name);
  if ((ignore_capacity != 0) && (ignore_snapshot != 0))
    return (NULL);

  /* Not found: allocate. */
  new = calloc(1, sizeof(*new));
  if (new == NULL)
    return (NULL);
  new->next = NULL;

  new->name = strdup(name);
  if (new->name == NULL) {
    sfree(new);
    return (NULL);
  }

  if (ignore_capacity == 0)
    new->flags |= CFG_VOLUME_USAGE_DF;
  if (ignore_snapshot == 0) {
    new->flags |= CFG_VOLUME_USAGE_SNAP;
    new->snap_query = na_elem_new("snapshot-list-info");
    na_child_add_string(new->snap_query, "target-type", "volume");
    na_child_add_string(new->snap_query, "target-name", name);
  } else {
    new->snap_query = NULL;
  }

  /* Add to end of list. */
  if (last == NULL)
    cvu->volumes = new;
  else
    last->next = new;

  return (new);
}