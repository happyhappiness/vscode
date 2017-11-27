int cf_util_get_boolean(const oconfig_item_t *ci, _Bool *ret_bool) /* {{{ */
{
  if ((ci == NULL) || (ret_bool == NULL))
    return (EINVAL);

  if ((ci->values_num != 1) || ((ci->values[0].type != OCONFIG_TYPE_BOOLEAN) &&
                                (ci->values[0].type != OCONFIG_TYPE_STRING))) {
    ERROR("cf_util_get_boolean: The %s option requires "
          "exactly one boolean argument.",
          ci->key);
    return (-1);
  }

  switch (ci->values[0].type) {
  case OCONFIG_TYPE_BOOLEAN:
    *ret_bool = ci->values[0].value.boolean ? 1 : 0;
    break;
  case OCONFIG_TYPE_STRING:
    WARNING("cf_util_get_boolean: Using string value `%s' for boolean option "
            "`%s' is deprecated and will be removed in future releases. "
            "Use unquoted true or false instead.",
            ci->values[0].value.string, ci->key);

    if (IS_TRUE(ci->values[0].value.string))
      *ret_bool = 1;
    else if (IS_FALSE(ci->values[0].value.string))
      *ret_bool = 0;
    else {
      ERROR("cf_util_get_boolean: Cannot parse string value `%s' of the `%s' "
            "option as a boolean value.",
            ci->values[0].value.string, ci->key);
      return (-1);
    }
    break;
  }

  return (0);
}