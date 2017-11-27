static void disk_submit(struct lv_block_info *binfo, virDomainPtr dom,
                        const char *dev) {
  char *dev_copy = strdup(dev);
  const char *type_instance = dev_copy;

  if (!dev_copy)
    return;

  if (blockdevice_format_basename && blockdevice_format == source)
    type_instance = basename(dev_copy);

  if (!type_instance) {
    sfree(dev_copy);
    return;
  }

  char flush_type_instance[DATA_MAX_NAME_LEN];
  snprintf(flush_type_instance, sizeof(flush_type_instance), "flush-%s",
           type_instance);

  if ((binfo->bi.rd_req != -1) && (binfo->bi.wr_req != -1))
    submit_derive2("disk_ops", (derive_t)binfo->bi.rd_req,
                   (derive_t)binfo->bi.wr_req, dom, type_instance);

  if ((binfo->bi.rd_bytes != -1) && (binfo->bi.wr_bytes != -1))
    submit_derive2("disk_octets", (derive_t)binfo->bi.rd_bytes,
                   (derive_t)binfo->bi.wr_bytes, dom, type_instance);

  if (extra_stats & ex_stats_disk) {
    if ((binfo->rd_total_times != -1) && (binfo->wr_total_times != -1))
      submit_derive2("disk_time", (derive_t)binfo->rd_total_times,
                     (derive_t)binfo->wr_total_times, dom, type_instance);

    if (binfo->fl_req != -1)
      submit(dom, "total_requests", flush_type_instance,
             &(value_t){.derive = (derive_t)binfo->fl_req}, 1);
    if (binfo->fl_total_times != -1) {
      derive_t value = binfo->fl_total_times / 1000; // ns -> ms
      submit(dom, "total_time_in_ms", flush_type_instance,
             &(value_t){.derive = value}, 1);
    }
  }

  sfree(dev_copy);
}