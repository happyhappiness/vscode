static int snmp_agent_set_vardata(void *data, size_t *data_len, u_char asn_type,
                                  double scale, double shift, const void *value,
                                  size_t len, int type) {

  int ret;
  netsnmp_vardata var;
  const value_t *val;
  long new_value = 0;

  val = value;
  var.string = (u_char *)data;

  ret = snmp_agent_get_value_from_ds_type(val, type, scale, shift, &new_value);
  if (ret != 0)
    return ret;

  switch (asn_type) {
  case ASN_INTEGER:
  case ASN_UINTEGER:
  case ASN_COUNTER:
  case ASN_TIMETICKS:
  case ASN_GAUGE:
    if (*data_len < sizeof(*var.integer))
      return -EINVAL;
    *var.integer = new_value;
    *data_len = sizeof(*var.integer);
    break;
  case ASN_COUNTER64:
    if (*data_len < sizeof(*var.counter64))
      return -EINVAL;
    var.counter64->high = (u_long)((int64_t)new_value >> 32);
    var.counter64->low = (u_long)((int64_t)new_value & 0xFFFFFFFF);
    *data_len = sizeof(*var.counter64);
    break;
  case ASN_OCTET_STR:
    if (type == DS_TYPE_GAUGE) {
      char buf[DATA_MAX_NAME_LEN];
      snprintf(buf, sizeof(buf), "%.2f", val->gauge);
      if (*data_len < strlen(buf))
        return -EINVAL;
      *data_len = strlen(buf);
      memcpy(var.string, buf, *data_len);
    } else {
      ERROR(PLUGIN_NAME ": Failed to convert %d ds type to %d asn type", type,
            asn_type);
      return -EINVAL;
    }
    break;
  default:
    ERROR(PLUGIN_NAME ": Failed to convert %d ds type to %d asn type", type,
          asn_type);
    return -EINVAL;
  }

  return 0;
}