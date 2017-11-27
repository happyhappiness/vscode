static int snmp_agent_get_value_from_ds_type(const value_t *val, int type,
                                             double scale, double shift,
                                             long *value) {
  switch (type) {
  case DS_TYPE_COUNTER:
    *value = (long)((val->counter * scale) + shift);
    break;
  case DS_TYPE_ABSOLUTE:
    *value = (long)((val->absolute * scale) + shift);
    break;
  case DS_TYPE_DERIVE:
    *value = (long)((val->derive * scale) + shift);
    break;
  case DS_TYPE_GAUGE:
    *value = (long)((val->gauge * scale) + shift);
    break;
  case TYPE_STRING:
    break;
  default:
    ERROR(PLUGIN_NAME ": Unknown data source type: %i", type);
    return -EINVAL;
  }

  return 0;
}