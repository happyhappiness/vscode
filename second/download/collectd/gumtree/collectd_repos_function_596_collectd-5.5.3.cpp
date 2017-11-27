static int agg_config_aggregation (oconfig_item_t *ci) /* {{{ */
{
  aggregation_t *agg;
  _Bool is_valid;
  int status;
  int i;

  agg = malloc (sizeof (*agg));
  if (agg == NULL)
  {
    ERROR ("aggregation plugin: malloc failed.");
    return (-1);
  }
  memset (agg, 0, sizeof (*agg));

  sstrncpy (agg->ident.host, "/.*/", sizeof (agg->ident.host));
  sstrncpy (agg->ident.plugin, "/.*/", sizeof (agg->ident.plugin));
  sstrncpy (agg->ident.plugin_instance, "/.*/",
      sizeof (agg->ident.plugin_instance));
  sstrncpy (agg->ident.type, "/.*/", sizeof (agg->ident.type));
  sstrncpy (agg->ident.type_instance, "/.*/",
      sizeof (agg->ident.type_instance));

  for (i = 0; i < ci->children_num; i++)
  {
    oconfig_item_t *child = ci->children + i;

    if (strcasecmp ("Host", child->key) == 0)
      cf_util_get_string_buffer (child, agg->ident.host,
          sizeof (agg->ident.host));
    else if (strcasecmp ("Plugin", child->key) == 0)
      cf_util_get_string_buffer (child, agg->ident.plugin,
          sizeof (agg->ident.plugin));
    else if (strcasecmp ("PluginInstance", child->key) == 0)
      cf_util_get_string_buffer (child, agg->ident.plugin_instance,
          sizeof (agg->ident.plugin_instance));
    else if (strcasecmp ("Type", child->key) == 0)
      cf_util_get_string_buffer (child, agg->ident.type,
          sizeof (agg->ident.type));
    else if (strcasecmp ("TypeInstance", child->key) == 0)
      cf_util_get_string_buffer (child, agg->ident.type_instance,
          sizeof (agg->ident.type_instance));
    else if (strcasecmp ("SetHost", child->key) == 0)
      cf_util_get_string (child, &agg->set_host);
    else if (strcasecmp ("SetPlugin", child->key) == 0)
      cf_util_get_string (child, &agg->set_plugin);
    else if (strcasecmp ("SetPluginInstance", child->key) == 0)
      cf_util_get_string (child, &agg->set_plugin_instance);
    else if (strcasecmp ("SetTypeInstance", child->key) == 0)
      cf_util_get_string (child, &agg->set_type_instance);
    else if (strcasecmp ("GroupBy", child->key) == 0)
      agg_config_handle_group_by (child, agg);
    else if (strcasecmp ("CalculateNum", child->key) == 0)
      cf_util_get_boolean (child, &agg->calc_num);
    else if (strcasecmp ("CalculateSum", child->key) == 0)
      cf_util_get_boolean (child, &agg->calc_sum);
    else if (strcasecmp ("CalculateAverage", child->key) == 0)
      cf_util_get_boolean (child, &agg->calc_average);
    else if (strcasecmp ("CalculateMinimum", child->key) == 0)
      cf_util_get_boolean (child, &agg->calc_min);
    else if (strcasecmp ("CalculateMaximum", child->key) == 0)
      cf_util_get_boolean (child, &agg->calc_max);
    else if (strcasecmp ("CalculateStddev", child->key) == 0)
      cf_util_get_boolean (child, &agg->calc_stddev);
    else
      WARNING ("aggregation plugin: The \"%s\" key is not allowed inside "
          "<Aggregation /> blocks and will be ignored.", child->key);
  }

  if (agg_is_regex (agg->ident.host))
    agg->regex_fields |= LU_GROUP_BY_HOST;
  if (agg_is_regex (agg->ident.plugin))
    agg->regex_fields |= LU_GROUP_BY_PLUGIN;
  if (agg_is_regex (agg->ident.plugin_instance))
    agg->regex_fields |= LU_GROUP_BY_PLUGIN_INSTANCE;
  if (agg_is_regex (agg->ident.type_instance))
    agg->regex_fields |= LU_GROUP_BY_TYPE_INSTANCE;

  /* Sanity checking */
  is_valid = 1;
  if (strcmp ("/.*/", agg->ident.type) == 0) /* {{{ */
  {
    ERROR ("aggregation plugin: It appears you did not specify the required "
        "\"Type\" option in this aggregation. "
        "(Host \"%s\", Plugin \"%s\", PluginInstance \"%s\", "
        "Type \"%s\", TypeInstance \"%s\")",
        agg->ident.host, agg->ident.plugin, agg->ident.plugin_instance,
        agg->ident.type, agg->ident.type_instance);
    is_valid = 0;
  }
  else if (strchr (agg->ident.type, '/') != NULL)
  {
    ERROR ("aggregation plugin: The \"Type\" may not contain the '/' "
        "character. Especially, it may not be a regex. The current "
        "value is \"%s\".", agg->ident.type);
    is_valid = 0;
  } /* }}} */

  /* Check that there is at least one regex field without a grouping. {{{ */
  if ((agg->regex_fields & ~agg->group_by) == 0)
  {
    ERROR ("aggregation plugin: An aggregation must contain at least one "
        "wildcard. This is achieved by leaving at least one of the \"Host\", "
        "\"Plugin\", \"PluginInstance\" and \"TypeInstance\" options blank "
        "or using a regular expression and not grouping by that field. "
        "(Host \"%s\", Plugin \"%s\", PluginInstance \"%s\", "
        "Type \"%s\", TypeInstance \"%s\")",
        agg->ident.host, agg->ident.plugin, agg->ident.plugin_instance,
        agg->ident.type, agg->ident.type_instance);
    is_valid = 0;
  } /* }}} */

  /* Check that all grouping fields are regular expressions. {{{ */
  if (agg->group_by & ~agg->regex_fields)
  {
    ERROR ("aggregation plugin: Only wildcard fields (fields for which a "
        "regular expression is configured or which are left blank) can be "
        "specified in the \"GroupBy\" option. "
        "(Host \"%s\", Plugin \"%s\", PluginInstance \"%s\", "
        "Type \"%s\", TypeInstance \"%s\")",
        agg->ident.host, agg->ident.plugin, agg->ident.plugin_instance,
        agg->ident.type, agg->ident.type_instance);
    is_valid = 0;
  } /* }}} */

  if (!agg->calc_num && !agg->calc_sum && !agg->calc_average /* {{{ */
      && !agg->calc_min && !agg->calc_max && !agg->calc_stddev)
  {
    ERROR ("aggregation plugin: No aggregation function has been specified. "
        "Without this, I don't know what I should be calculating. "
        "(Host \"%s\", Plugin \"%s\", PluginInstance \"%s\", "
        "Type \"%s\", TypeInstance \"%s\")",
        agg->ident.host, agg->ident.plugin, agg->ident.plugin_instance,
        agg->ident.type, agg->ident.type_instance);
    is_valid = 0;
  } /* }}} */

  if (!is_valid) /* {{{ */
  {
    sfree (agg);
    return (-1);
  } /* }}} */

  status = lookup_add (lookup, &agg->ident, agg->group_by, agg);
  if (status != 0)
  {
    ERROR ("aggregation plugin: lookup_add failed with status %i.", status);
    sfree (agg);
    return (-1);
  }

  DEBUG ("aggregation plugin: Successfully added aggregation: "
      "(Host \"%s\", Plugin \"%s\", PluginInstance \"%s\", "
      "Type \"%s\", TypeInstance \"%s\")",
      agg->ident.host, agg->ident.plugin, agg->ident.plugin_instance,
      agg->ident.type, agg->ident.type_instance);
  return (0);
}