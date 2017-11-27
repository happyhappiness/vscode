static int tr_meta_data_action_invoke(/* {{{ */
                                      tr_meta_data_action_t *act_head,
                                      meta_data_t **dest) {
  int status;
  regmatch_t matches[8] = {[0] = {0}};

  if (act_head == NULL)
    return (-EINVAL);

  if ((*dest) == NULL) /* nothing to do */
    return (0);

  for (tr_meta_data_action_t *act = act_head; act != NULL; act = act->next) {
    char temp[DATA_MAX_NAME_LEN];
    char *subst_status;
    int value_type;
    int meta_data_status;
    char *value;
    meta_data_t *result;

    value_type = meta_data_type(*dest, act->key);
    if (value_type == 0) /* not found */
      continue;
    if (value_type != MD_TYPE_STRING) {
      WARNING("Target `replace': Attempting replace on metadata key `%s', "
              "which isn't a string.",
              act->key);
      continue;
    }

    meta_data_status = meta_data_get_string(*dest, act->key, &value);
    if (meta_data_status != 0) {
      ERROR("Target `replace': Unable to retrieve metadata value for `%s'.",
            act->key);
      return (meta_data_status);
    }

    DEBUG("target_replace plugin: tr_meta_data_action_invoke: `%s' "
          "old value = `%s'",
          act->key, value);

    status = regexec(&act->re, value, STATIC_ARRAY_SIZE(matches), matches,
                     /* flags = */ 0);
    if (status == REG_NOMATCH) {
      sfree(value);
      continue;
    } else if (status != 0) {
      char errbuf[1024] = "";

      regerror(status, &act->re, errbuf, sizeof(errbuf));
      ERROR("Target `replace': Executing a regular expression failed: %s.",
            errbuf);
      sfree(value);
      continue;
    }

    if (act->replacement == NULL) {
      /* no replacement; delete the key */
      DEBUG("target_replace plugin: tr_meta_data_action_invoke: "
            "deleting `%s'",
            act->key);
      meta_data_delete(*dest, act->key);
      sfree(value);
      continue;
    }

    subst_status = subst(temp, sizeof(temp), value, (size_t)matches[0].rm_so,
                         (size_t)matches[0].rm_eo, act->replacement);
    if (subst_status == NULL) {
      ERROR("Target `replace': subst (value = %s, start = %zu, end = %zu, "
            "replacement = %s) failed.",
            value, (size_t)matches[0].rm_so, (size_t)matches[0].rm_eo,
            act->replacement);
      sfree(value);
      continue;
    }

    DEBUG("target_replace plugin: tr_meta_data_action_invoke: `%s' "
          "value `%s' -> `%s'",
          act->key, value, temp);

    if ((result = meta_data_create()) == NULL) {
      ERROR("Target `replace': failed to create metadata for `%s'.", act->key);
      sfree(value);
      return (-ENOMEM);
    }

    meta_data_status = meta_data_add_string(result, act->key, temp);
    if (meta_data_status != 0) {
      ERROR("Target `replace': Unable to set metadata value for `%s'.",
            act->key);
      meta_data_destroy(result);
      sfree(value);
      return (meta_data_status);
    }

    meta_data_clone_merge(dest, result);
    meta_data_destroy(result);
    sfree(value);
  } /* for (act = act_head; act != NULL; act = act->next) */

  return (0);
}