int cf_util_get_cdtime(const oconfig_item_t *ci, cdtime_t *ret_value) /* {{{ */
{
  if ((ci == NULL) || (ret_value == NULL))
    return (EINVAL);

  if ((ci->values_num != 1) || (ci->values[0].type != OCONFIG_TYPE_NUMBER)) {
    ERROR("cf_util_get_cdtime: The %s option requires "
          "exactly one numeric argument.",
          ci->key);
    return (-1);
  }

  if (ci->values[0].value.number < 0.0) {
    ERROR("cf_util_get_cdtime: The numeric argument of the %s "
          "option must not be negative.",
          ci->key);
    return (-1);
  }

  *ret_value = DOUBLE_TO_CDTIME_T(ci->values[0].value.number);

  return (0);
}