static int udb_config_set_uint(unsigned int *ret_value, /* {{{ */
                               oconfig_item_t *ci) {
  double tmp;

  if ((ci->values_num != 1) || (ci->values[0].type != OCONFIG_TYPE_NUMBER)) {
    WARNING("db query utils: The `%s' config option "
            "needs exactly one numeric argument.",
            ci->key);
    return (-1);
  }

  tmp = ci->values[0].value.number;
  if ((tmp < 0.0) || (tmp > ((double)UINT_MAX)))
    return (-ERANGE);

  *ret_value = (unsigned int)(tmp + .5);
  return (0);
}