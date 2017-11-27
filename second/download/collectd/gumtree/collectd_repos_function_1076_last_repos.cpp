static int mcelog_submit(const mcelog_memory_rec_t *mr) {

  if (!mr) {
    ERROR(MCELOG_PLUGIN ": %s: NULL pointer", __FUNCTION__);
    return -1;
  }

  llentry_t *dimm = mcelog_dimm(mr, g_mcelog_config.dimms_list);
  if (dimm == NULL) {
    ERROR(MCELOG_PLUGIN
          ": Error adding/getting dimm memory item to/from cache");
    return -1;
  }

  value_list_t vl = {
      .values_len = 1,
      .values = &(value_t){.derive = (derive_t)mr->corrected_err_total},
      .time = cdtime(),
      .plugin = MCELOG_PLUGIN,
      .type = "errors",
      .type_instance = MCELOG_CORRECTED_ERR_TYPE_INS};

  mcelog_update_dimm_stats(dimm, mr);

  if (mr->dimm_name[0] != '\0')
    snprintf(vl.plugin_instance, sizeof(vl.plugin_instance), "%s_%s",
             mr->location, mr->dimm_name);
  else
    sstrncpy(vl.plugin_instance, mr->location, sizeof(vl.plugin_instance));

  plugin_dispatch_values(&vl);

  snprintf(vl.type_instance, sizeof(vl.type_instance),
           "corrected_memory_errors_in_%s", mr->corrected_err_timed_period);
  vl.values = &(value_t){.derive = (derive_t)mr->corrected_err_timed};
  plugin_dispatch_values(&vl);

  sstrncpy(vl.type_instance, MCELOG_UNCORRECTED_ERR_TYPE_INS,
           sizeof(vl.type_instance));
  vl.values = &(value_t){.derive = (derive_t)mr->uncorrected_err_total};
  plugin_dispatch_values(&vl);

  snprintf(vl.type_instance, sizeof(vl.type_instance),
           "uncorrected_memory_errors_in_%s", mr->uncorrected_err_timed_period);
  vl.values = &(value_t){.derive = (derive_t)mr->uncorrected_err_timed};
  plugin_dispatch_values(&vl);

  return 0;
}