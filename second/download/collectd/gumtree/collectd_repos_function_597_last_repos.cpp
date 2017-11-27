static int agg_instance_create_name(agg_instance_t *inst, /* {{{ */
                                    value_list_t const *vl,
                                    aggregation_t const *agg) {
#define COPY_FIELD(buffer, buffer_size, field, group_mask, all_value)          \
  do {                                                                         \
    if (agg->set_##field != NULL)                                              \
      sstrncpy(buffer, agg->set_##field, buffer_size);                         \
    else if ((agg->regex_fields & group_mask) && (agg->group_by & group_mask)) \
      sstrncpy(buffer, vl->field, buffer_size);                                \
    else if ((agg->regex_fields & group_mask) &&                               \
             (AGG_MATCHES_ALL(agg->ident.field)))                              \
      sstrncpy(buffer, all_value, buffer_size);                                \
    else                                                                       \
      sstrncpy(buffer, agg->ident.field, buffer_size);                         \
  } while (0)

  /* Host */
  COPY_FIELD(inst->ident.host, sizeof(inst->ident.host), host, LU_GROUP_BY_HOST,
             "global");

  /* Plugin */
  if (agg->set_plugin != NULL)
    sstrncpy(inst->ident.plugin, agg->set_plugin, sizeof(inst->ident.plugin));
  else
    sstrncpy(inst->ident.plugin, "aggregation", sizeof(inst->ident.plugin));

  /* Plugin instance */
  if (agg->set_plugin_instance != NULL)
    sstrncpy(inst->ident.plugin_instance, agg->set_plugin_instance,
             sizeof(inst->ident.plugin_instance));
  else {
    char tmp_plugin[DATA_MAX_NAME_LEN];
    char tmp_plugin_instance[DATA_MAX_NAME_LEN] = "";

    if ((agg->regex_fields & LU_GROUP_BY_PLUGIN) &&
        (agg->group_by & LU_GROUP_BY_PLUGIN))
      sstrncpy(tmp_plugin, vl->plugin, sizeof(tmp_plugin));
    else if ((agg->regex_fields & LU_GROUP_BY_PLUGIN) &&
             (AGG_MATCHES_ALL(agg->ident.plugin)))
      sstrncpy(tmp_plugin, "", sizeof(tmp_plugin));
    else
      sstrncpy(tmp_plugin, agg->ident.plugin, sizeof(tmp_plugin));

    if ((agg->regex_fields & LU_GROUP_BY_PLUGIN_INSTANCE) &&
        (agg->group_by & LU_GROUP_BY_PLUGIN_INSTANCE))
      sstrncpy(tmp_plugin_instance, vl->plugin_instance,
               sizeof(tmp_plugin_instance));
    else if ((agg->regex_fields & LU_GROUP_BY_PLUGIN_INSTANCE) &&
             (AGG_MATCHES_ALL(agg->ident.plugin_instance)))
      sstrncpy(tmp_plugin_instance, "", sizeof(tmp_plugin_instance));
    else
      sstrncpy(tmp_plugin_instance, agg->ident.plugin_instance,
               sizeof(tmp_plugin_instance));

    if ((strcmp("", tmp_plugin) == 0) && (strcmp("", tmp_plugin_instance) == 0))
      sstrncpy(inst->ident.plugin_instance, AGG_FUNC_PLACEHOLDER,
               sizeof(inst->ident.plugin_instance));
    else if (strcmp("", tmp_plugin) != 0)
      snprintf(inst->ident.plugin_instance, sizeof(inst->ident.plugin_instance),
               "%s-%s", tmp_plugin, AGG_FUNC_PLACEHOLDER);
    else if (strcmp("", tmp_plugin_instance) != 0)
      snprintf(inst->ident.plugin_instance, sizeof(inst->ident.plugin_instance),
               "%s-%s", tmp_plugin_instance, AGG_FUNC_PLACEHOLDER);
    else
      snprintf(inst->ident.plugin_instance, sizeof(inst->ident.plugin_instance),
               "%s-%s-%s", tmp_plugin, tmp_plugin_instance,
               AGG_FUNC_PLACEHOLDER);
  }

  /* Type */
  sstrncpy(inst->ident.type, agg->ident.type, sizeof(inst->ident.type));

  /* Type instance */
  COPY_FIELD(inst->ident.type_instance, sizeof(inst->ident.type_instance),
             type_instance, LU_GROUP_BY_TYPE_INSTANCE, "");

#undef COPY_FIELD

  return 0;
}