static int tr_config_add_action(tr_action_t **dest, /* {{{ */
                                const oconfig_item_t *ci, int may_be_empty) {
  tr_action_t *act;
  int status;

  if (dest == NULL)
    return (-EINVAL);

  if ((ci->values_num != 2) || (ci->values[0].type != OCONFIG_TYPE_STRING) ||
      (ci->values[1].type != OCONFIG_TYPE_STRING)) {
    ERROR("Target `replace': The `%s' option requires exactly two string "
          "arguments.",
          ci->key);
    return (-1);
  }

  act = calloc(1, sizeof(*act));
  if (act == NULL) {
    ERROR("tr_config_add_action: calloc failed.");
    return (-ENOMEM);
  }

  act->replacement = NULL;
  act->may_be_empty = may_be_empty;

  status = regcomp(&act->re, ci->values[0].value.string, REG_EXTENDED);
  if (status != 0) {
    char errbuf[1024] = "";

    /* regerror assures null termination. */
    regerror(status, &act->re, errbuf, sizeof(errbuf));
    ERROR("Target `replace': Compiling the regular expression `%s' "
          "failed: %s.",
          ci->values[0].value.string, errbuf);
    sfree(act);
    return (-EINVAL);
  }

  act->replacement = tr_strdup(ci->values[1].value.string);
  if (act->replacement == NULL) {
    ERROR("tr_config_add_action: tr_strdup failed.");
    regfree(&act->re);
    sfree(act);
    return (-ENOMEM);
  }

  /* Insert action at end of list. */
  if (*dest == NULL)
    *dest = act;
  else {
    tr_action_t *prev;

    prev = *dest;
    while (prev->next != NULL)
      prev = prev->next;

    prev->next = act;
  }

  return (0);
}