static int mv_config_add_boolean(int *ret_value, /* {{{ */
                                 oconfig_item_t *ci) {

  if ((ci->values_num != 1) || (ci->values[0].type != OCONFIG_TYPE_BOOLEAN)) {
    ERROR("`value' match: `%s' needs exactly one boolean argument.", ci->key);
    return -1;
  }

  if (ci->values[0].value.boolean)
    *ret_value = 1;
  else
    *ret_value = 0;

  return 0;
}