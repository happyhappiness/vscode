static int nagios_config(oconfig_item_t *ci) /* {{{ */
{
  for (int i = 0; i < ci->children_num; i++) {
    oconfig_item_t *child = ci->children + i;

    if (strcasecmp("CommandFile", child->key) == 0)
      cf_util_get_string(child, &nagios_command_file);
    else
      WARNING("notify_nagios plugin: Ignoring unknown config option \"%s\".",
              child->key);
  }

  return 0;
}