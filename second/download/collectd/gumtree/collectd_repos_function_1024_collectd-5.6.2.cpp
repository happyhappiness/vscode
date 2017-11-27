static int tn_config_add_string(char **dest, /* {{{ */
                                const oconfig_item_t *ci) {
  char *temp;

  if (dest == NULL)
    return (-EINVAL);

  if ((ci->values_num != 1) || (ci->values[0].type != OCONFIG_TYPE_STRING)) {
    ERROR("Target `notification': The `%s' option requires exactly one string "
          "argument.",
          ci->key);
    return (-1);
  }

  if (ci->values[0].value.string[0] == 0) {
    ERROR(
        "Target `notification': The `%s' option does not accept empty strings.",
        ci->key);
    return (-1);
  }

  temp = sstrdup(ci->values[0].value.string);
  if (temp == NULL) {
    ERROR("tn_config_add_string: sstrdup failed.");
    return (-1);
  }

  free(*dest);
  *dest = temp;

  return (0);
}