int cf_util_get_string(const oconfig_item_t *ci, char **ret_string) /* {{{ */
{
  char *string;

  if ((ci->values_num != 1) || (ci->values[0].type != OCONFIG_TYPE_STRING)) {
    ERROR("cf_util_get_string: The %s option requires "
          "exactly one string argument.",
          ci->key);
    return (-1);
  }

  string = strdup(ci->values[0].value.string);
  if (string == NULL)
    return (-1);

  if (*ret_string != NULL)
    sfree(*ret_string);
  *ret_string = string;

  return (0);
}