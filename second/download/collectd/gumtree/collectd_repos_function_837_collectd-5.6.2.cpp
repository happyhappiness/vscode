static int bind_config_set_bool(const char *name, int *var, /* {{{ */
                                oconfig_item_t *ci) {
  if ((ci->values_num != 1) || (ci->values[0].type != OCONFIG_TYPE_BOOLEAN)) {
    WARNING("bind plugin: The `%s' option needs "
            "exactly one boolean argument.",
            name);
    return (-1);
  }

  if (ci->values[0].value.boolean)
    *var = 1;
  else
    *var = 0;
  return 0;
}