int cf_util_get_port_number(const oconfig_item_t *ci) /* {{{ */
{
  int tmp;

  if ((ci->values_num != 1) || ((ci->values[0].type != OCONFIG_TYPE_STRING) &&
                                (ci->values[0].type != OCONFIG_TYPE_NUMBER))) {
    ERROR("cf_util_get_port_number: The \"%s\" option requires "
          "exactly one string argument.",
          ci->key);
    return -1;
  }

  if (ci->values[0].type == OCONFIG_TYPE_STRING)
    return service_name_to_port_number(ci->values[0].value.string);

  assert(ci->values[0].type == OCONFIG_TYPE_NUMBER);
  tmp = (int)(ci->values[0].value.number + 0.5);
  if ((tmp < 1) || (tmp > 65535)) {
    ERROR("cf_util_get_port_number: The \"%s\" option requires "
          "a service name or a port number. The number "
          "you specified, %i, is not in the valid "
          "range of 1-65535.",
          ci->key, tmp);
    return -1;
  }

  return tmp;
}