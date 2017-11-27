int cf_util_get_boolean(const oconfig_item_t *ci, _Bool *ret_bool) /* {{{ */
{
  if ((ci == NULL) || (ret_bool == NULL))
    return (EINVAL);

  if ((ci->values_num != 1) || (ci->values[0].type != OCONFIG_TYPE_BOOLEAN)) {
    ERROR("cf_util_get_boolean: The %s option requires "
          "exactly one boolean argument.",
          ci->key);
    return (-1);
  }

  *ret_bool = ci->values[0].value.boolean ? 1 : 0;

  return (0);
}