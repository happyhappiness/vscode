static int cconn_process_data(struct cconn *io, yajl_struct *yajl,
                              yajl_handle hand) {
  int ret;
  struct values_tmp *vtmp = calloc(1, sizeof(struct values_tmp) * 1);
  if (!vtmp) {
    return -ENOMEM;
  }

  vtmp->vlist = (value_list_t)VALUE_LIST_INIT;
  sstrncpy(vtmp->vlist.plugin, "ceph", sizeof(vtmp->vlist.plugin));
  sstrncpy(vtmp->vlist.plugin_instance, io->d->name,
           sizeof(vtmp->vlist.plugin_instance));

  vtmp->d = io->d;
  vtmp->avgcount_exists = -1;
  vtmp->latency_index = 0;
  vtmp->index = 0;
  yajl->handler_arg = vtmp;
  ret = traverse_json(io->json, io->json_len, hand);
  sfree(vtmp);
  return ret;
}