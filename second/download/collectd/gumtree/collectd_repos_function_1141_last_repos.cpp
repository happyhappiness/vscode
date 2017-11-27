static int cna_setup_volume_perf(cfg_volume_perf_t *cd) /* {{{ */
{
  na_elem_t *e;

  if (cd == NULL)
    return EINVAL;

  if (cd->query != NULL)
    return 0;

  cd->query = na_elem_new("perf-object-get-instances");
  if (cd->query == NULL) {
    ERROR("netapp plugin: na_elem_new failed.");
    return -1;
  }
  na_child_add_string(cd->query, "objectname", "volume");

  e = na_elem_new("counters");
  if (e == NULL) {
    na_elem_free(cd->query);
    cd->query = NULL;
    ERROR("netapp plugin: na_elem_new failed.");
    return -1;
  }
  na_child_add_string(e, "counter", "read_ops");
  na_child_add_string(e, "counter", "write_ops");
  na_child_add_string(e, "counter", "read_data");
  na_child_add_string(e, "counter", "write_data");
  na_child_add_string(e, "counter", "read_latency");
  na_child_add_string(e, "counter", "write_latency");
  na_child_add(cd->query, e);

  return 0;
}