static int pplugin_write(pTHX_ const char *plugin, AV *data_set, HV *values) {
  data_set_t ds;
  value_list_t vl = VALUE_LIST_INIT;

  int ret;

  if (NULL == values)
    return -1;

  if (0 != hv2value_list(aTHX_ values, &vl))
    return -1;

  if ((NULL != data_set) && (0 != av2data_set(aTHX_ data_set, vl.type, &ds)))
    return -1;

  ret = plugin_write(plugin, NULL == data_set ? NULL : &ds, &vl);
  if (0 != ret)
    log_warn("Dispatching value to plugin \"%s\" failed with status %i.",
             NULL == plugin ? "<any>" : plugin, ret);

  if (NULL != data_set)
    sfree(ds.ds);
  sfree(vl.values);
  return ret;
}