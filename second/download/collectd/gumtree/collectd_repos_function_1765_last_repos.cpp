static int wrr_write(const data_set_t *ds, /* {{{ */
                     const value_list_t *vl, user_data_t *ud) {
  int status = 0;
  int statuses[vl->values_len];
  struct riemann_host *host = ud->data;
  riemann_message_t *msg;

  if (host->check_thresholds) {
    status = write_riemann_threshold_check(ds, vl, statuses);
    if (status != 0)
      return status;
  } else {
    memset(statuses, 0, sizeof(statuses));
  }

  if (host->client_type != RIEMANN_CLIENT_UDP && host->batch_mode) {
    wrr_batch_add_value_list(host, ds, vl, statuses);
  } else {
    msg = wrr_value_list_to_message(host, ds, vl, statuses);
    if (msg == NULL)
      return -1;

    status = wrr_send(host, msg);

    riemann_message_free(msg);
  }
  return status;
}