static int update_last(struct ceph_daemon *d, const char *ds_n, int index,
                       double cur_sum, uint64_t cur_count) {
  if ((d->last_idx > index) &&
      (strcmp(d->last_poll_data[index]->ds_name, ds_n) == 0)) {
    d->last_poll_data[index]->last_sum = cur_sum;
    d->last_poll_data[index]->last_count = cur_count;
    return 0;
  }

  if (!d->last_poll_data) {
    d->last_poll_data = malloc(sizeof(*d->last_poll_data));
    if (!d->last_poll_data) {
      return -ENOMEM;
    }
  } else {
    struct last_data **tmp_last = realloc(
        d->last_poll_data, ((d->last_idx + 1) * sizeof(struct last_data *)));
    if (!tmp_last) {
      return -ENOMEM;
    }
    d->last_poll_data = tmp_last;
  }
  return add_last(d, ds_n, cur_sum, cur_count);
}