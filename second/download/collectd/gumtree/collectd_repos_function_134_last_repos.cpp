static int exec_config(oconfig_item_t *ci) /* {{{ */
{
  for (int i = 0; i < ci->children_num; i++) {
    oconfig_item_t *child = ci->children + i;
    if ((strcasecmp("Exec", child->key) == 0) ||
        (strcasecmp("NotificationExec", child->key) == 0))
      exec_config_exec(child);
    else {
      WARNING("exec plugin: Unknown config option `%s'.", child->key);
    }
  } /* for (i) */

  return 0;
}