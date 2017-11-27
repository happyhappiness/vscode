static int agg_config_handle_group_by(oconfig_item_t const *ci, /* {{{ */
                                      aggregation_t *agg) {
  for (int i = 0; i < ci->values_num; i++) {
    char const *value;

    if (ci->values[i].type != OCONFIG_TYPE_STRING) {
      ERROR("aggregation plugin: Argument %i of the \"GroupBy\" option "
            "is not a string.",
            i + 1);
      continue;
    }

    value = ci->values[i].value.string;

    if (strcasecmp("Host", value) == 0)
      agg->group_by |= LU_GROUP_BY_HOST;
    else if (strcasecmp("Plugin", value) == 0)
      agg->group_by |= LU_GROUP_BY_PLUGIN;
    else if (strcasecmp("PluginInstance", value) == 0)
      agg->group_by |= LU_GROUP_BY_PLUGIN_INSTANCE;
    else if (strcasecmp("TypeInstance", value) == 0)
      agg->group_by |= LU_GROUP_BY_TYPE_INSTANCE;
    else if (strcasecmp("Type", value) == 0)
      ERROR("aggregation plugin: Grouping by type is not supported.");
    else
      WARNING("aggregation plugin: The \"%s\" argument to the \"GroupBy\" "
              "option is invalid and will be ignored.",
              value);
  } /* for (ci->values) */

  return 0;
}