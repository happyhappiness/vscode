static int ts_util_get_key_and_string_wo_strdup(const oconfig_item_t *ci,
                                                char **ret_key,
                                                char **ret_string) /* {{{ */
{
  if ((ci->values_num != 2) || (ci->values[0].type != OCONFIG_TYPE_STRING) ||
      (ci->values[1].type != OCONFIG_TYPE_STRING)) {
    ERROR("ts_util_get_key_and_string_wo_strdup: The %s option requires "
          "exactly two string arguments.",
          ci->key);
    return -1;
  }

  *ret_key = ci->values[0].value.string;
  *ret_string = ci->values[1].value.string;

  return 0;
}