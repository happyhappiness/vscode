static void report_thin_pool_utilization(lv_t lv, char const *vg_name,
                                         uint64_t lv_size) {
  char const *data_lv;
  char const *metadata_lv;
  uint64_t metadata_size;

  data_lv = get_lv_property_string(lv, "data_lv");
  metadata_lv = get_lv_property_string(lv, "metadata_lv");
  metadata_size = get_lv_property_int(lv, "lv_metadata_size");
  if (data_lv == NULL || metadata_lv == NULL || metadata_size == NO_VALUE)
    return;

  report_lv_utilization(lv, vg_name, data_lv, lv_size, "data_percent");
  report_lv_utilization(lv, vg_name, metadata_lv, metadata_size,
                        "metadata_percent");
}