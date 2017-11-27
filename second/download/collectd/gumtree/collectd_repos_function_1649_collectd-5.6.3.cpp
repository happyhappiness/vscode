static void ceph_daemon_free(struct ceph_daemon *d) {
  for (int i = 0; i < d->last_idx; i++) {
    sfree(d->last_poll_data[i]);
  }
  sfree(d->last_poll_data);
  d->last_poll_data = NULL;
  d->last_idx = 0;

  for (int i = 0; i < d->ds_num; i++) {
    sfree(d->ds_names[i]);
  }
  sfree(d->ds_types);
  sfree(d->ds_names);
  sfree(d);
}