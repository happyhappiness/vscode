meta_data_t *pmu_meta_data_create(const struct efd *efd) {
  meta_data_t *meta = NULL;

  /* create meta data only if value was scaled */
  if (efd->val[1] == efd->val[2] || !efd->val[2]) {
    return NULL;
  }

  meta = meta_data_create();
  if (meta == NULL) {
    ERROR(PMU_PLUGIN ": meta_data_create failed.");
    return NULL;
  }

  meta_data_add_unsigned_int(meta, "intel_pmu:raw_count", efd->val[0]);
  meta_data_add_unsigned_int(meta, "intel_pmu:time_enabled", efd->val[1]);
  meta_data_add_unsigned_int(meta, "intel_pmu:time_running", efd->val[2]);

  return meta;
}