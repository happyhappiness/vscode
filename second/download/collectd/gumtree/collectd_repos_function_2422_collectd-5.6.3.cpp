static int fc_config_add_target(fc_target_t **targets_head, /* {{{ */
                                oconfig_item_t *ci) {
  fc_target_t *t;
  fc_target_t *ptr;
  int status;

  if ((ci->values_num != 1) || (ci->values[0].type != OCONFIG_TYPE_STRING)) {
    WARNING("Filter subsystem: `Target' blocks require "
            "exactly one string argument.");
    return (-1);
  }

  ptr = target_list_head;
  while (ptr != NULL) {
    if (strcasecmp(ptr->name, ci->values[0].value.string) == 0)
      break;
    ptr = ptr->next;
  }

  if (ptr == NULL) {
    WARNING("Filter subsystem: Cannot find a \"%s\" target. "
            "Did you load the appropriate plugin?",
            ci->values[0].value.string);
    return (-1);
  }

  t = calloc(1, sizeof(*t));
  if (t == NULL) {
    ERROR("fc_config_add_target: calloc failed.");
    return (-1);
  }

  sstrncpy(t->name, ptr->name, sizeof(t->name));
  memcpy(&t->proc, &ptr->proc, sizeof(t->proc));
  t->user_data = NULL;
  t->next = NULL;

  if (t->proc.create != NULL) {
    status = (*t->proc.create)(ci, &t->user_data);
    if (status != 0) {
      WARNING("Filter subsystem: Failed to create a %s target.", t->name);
      fc_free_targets(t);
      return (-1);
    }
  } else {
    t->user_data = NULL;
  }

  if (*targets_head != NULL) {
    ptr = *targets_head;
    while (ptr->next != NULL)
      ptr = ptr->next;

    ptr->next = t;
  } else {
    *targets_head = t;
  }

  return (0);
}