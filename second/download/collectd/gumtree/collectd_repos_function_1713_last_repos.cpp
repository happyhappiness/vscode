static int tr_config_add_meta_action(tr_meta_data_action_t **dest, /* {{{ */
                                     const oconfig_item_t *ci,
                                     _Bool should_delete) {
  tr_meta_data_action_t *act;
  int status;

  if (dest == NULL)
    return -EINVAL;

  if (should_delete) {
    if ((ci->values_num != 2) || (ci->values[0].type != OCONFIG_TYPE_STRING) ||
        (ci->values[1].type != OCONFIG_TYPE_STRING)) {
      ERROR("Target `replace': The `%s' option requires exactly two string "
            "arguments.",
            ci->key);
      return -1;
    }
  } else {
    if ((ci->values_num != 3) || (ci->values[0].type != OCONFIG_TYPE_STRING) ||
        (ci->values[1].type != OCONFIG_TYPE_STRING) ||
        (ci->values[2].type != OCONFIG_TYPE_STRING)) {
      ERROR("Target `replace': The `%s' option requires exactly three string "
            "arguments.",
            ci->key);
      return -1;
    }
  }

  if (strlen(ci->values[0].value.string) == 0) {
    ERROR("Target `replace': The `%s' option does not accept empty string as "
          "first argument.",
          ci->key);
    return -1;
  }

  act = calloc(1, sizeof(*act));
  if (act == NULL) {
    ERROR("tr_config_add_meta_action: calloc failed.");
    return -ENOMEM;
  }

  act->key = NULL;
  act->replacement = NULL;

  status = regcomp(&act->re, ci->values[1].value.string, REG_EXTENDED);
  if (status != 0) {
    char errbuf[1024] = "";

    /* regerror assures null termination. */
    regerror(status, &act->re, errbuf, sizeof(errbuf));
    ERROR("Target `replace': Compiling the regular expression `%s' "
          "failed: %s.",
          ci->values[1].value.string, errbuf);
    sfree(act->key);
    sfree(act);
    return -EINVAL;
  }

  act->key = tr_strdup(ci->values[0].value.string);
  if (act->key == NULL) {
    ERROR("tr_config_add_meta_action: tr_strdup failed.");
    tr_meta_data_action_destroy(act);
    return -ENOMEM;
  }

  if (!should_delete) {
    act->replacement = tr_strdup(ci->values[2].value.string);
    if (act->replacement == NULL) {
      ERROR("tr_config_add_meta_action: tr_strdup failed.");
      tr_meta_data_action_destroy(act);
      return -ENOMEM;
    }
  }

  /* Insert action at end of list. */
  if (*dest == NULL)
    *dest = act;
  else {
    tr_meta_data_action_t *prev;

    prev = *dest;
    while (prev->next != NULL)
      prev = prev->next;

    prev->next = act;
  }

  return 0;
}