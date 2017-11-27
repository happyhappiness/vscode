static int fc_config_add_rule(fc_chain_t *chain, /* {{{ */
                              oconfig_item_t *ci) {
  fc_rule_t *rule;
  char rule_name[2 * DATA_MAX_NAME_LEN] = "Unnamed rule";
  int status = 0;

  if (ci->values_num > 1) {
    WARNING("Filter subsystem: `Rule' blocks have at most one argument.");
    return (-1);
  } else if ((ci->values_num == 1) &&
             (ci->values[0].type != OCONFIG_TYPE_STRING)) {
    WARNING("Filter subsystem: `Rule' blocks expect one string argument "
            "or no argument at all.");
    return (-1);
  }

  rule = calloc(1, sizeof(*rule));
  if (rule == NULL) {
    ERROR("fc_config_add_rule: calloc failed.");
    return (-1);
  }

  if (ci->values_num == 1) {
    sstrncpy(rule->name, ci->values[0].value.string, sizeof(rule->name));
    ssnprintf(rule_name, sizeof(rule_name), "Rule \"%s\"",
              ci->values[0].value.string);
  }

  for (int i = 0; i < ci->children_num; i++) {
    oconfig_item_t *option = ci->children + i;

    if (strcasecmp("Match", option->key) == 0)
      status = fc_config_add_match(&rule->matches, option);
    else if (strcasecmp("Target", option->key) == 0)
      status = fc_config_add_target(&rule->targets, option);
    else {
      WARNING("Filter subsystem: %s: Option `%s' not allowed "
              "inside a <Rule> block.",
              rule_name, option->key);
      status = -1;
    }

    if (status != 0)
      break;
  } /* for (ci->children) */

  /* Additional sanity checking. */
  while (status == 0) {
    if (rule->targets == NULL) {
      WARNING("Filter subsystem: %s: No target has been specified.", rule_name);
      status = -1;
      break;
    }

    break;
  } /* while (status == 0) */

  if (status != 0) {
    fc_free_rules(rule);
    return (-1);
  }

  if (chain->rules != NULL) {
    fc_rule_t *ptr;

    ptr = chain->rules;
    while (ptr->next != NULL)
      ptr = ptr->next;

    ptr->next = rule;
  } else {
    chain->rules = rule;
  }

  return (0);
}