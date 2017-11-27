static double get_last_avg(struct ceph_daemon *d, const char *ds_n, int index,
                           double cur_sum, uint64_t cur_count) {
  double result = -1.1, sum_delt = 0.0;
  uint64_t count_delt = 0;
  int tmp_index = 0;
  if (d->last_idx > index) {
    if (strcmp(d->last_poll_data[index]->ds_name, ds_n) == 0) {
      tmp_index = index;
    }
    // test previous index
    else if ((index > 0) &&
             (strcmp(d->last_poll_data[index - 1]->ds_name, ds_n) == 0)) {
      tmp_index = (index - 1);
    } else {
      tmp_index = backup_search_for_last_avg(d, ds_n);
    }

    if ((tmp_index > -1) &&
        (cur_count > d->last_poll_data[tmp_index]->last_count)) {
      sum_delt = (cur_sum - d->last_poll_data[tmp_index]->last_sum);
      count_delt = (cur_count - d->last_poll_data[tmp_index]->last_count);
      result = (sum_delt / count_delt);
    }
  }

  if (result == -1.1) {
    result = NAN;
  }
  if (update_last(d, ds_n, tmp_index, cur_sum, cur_count) == -ENOMEM) {
    return -ENOMEM;
  }
  return result;
}