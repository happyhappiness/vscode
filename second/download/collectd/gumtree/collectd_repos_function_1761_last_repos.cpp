static riemann_message_t *
wrr_value_list_to_message(struct riemann_host const *host, /* {{{ */
                          data_set_t const *ds, value_list_t const *vl,
                          int *statuses) {
  riemann_message_t *msg;
  size_t i;
  gauge_t *rates = NULL;

  /* Initialize the Msg structure. */
  msg = riemann_message_new();
  if (msg == NULL) {
    ERROR("write_riemann plugin: riemann_message_new failed.");
    return NULL;
  }

  if (host->store_rates) {
    rates = uc_get_rate(ds, vl);
    if (rates == NULL) {
      ERROR("write_riemann plugin: uc_get_rate failed.");
      riemann_message_free(msg);
      return NULL;
    }
  }

  for (i = 0; i < vl->values_len; i++) {
    riemann_event_t *event;

    event = wrr_value_to_event(host, ds, vl, (int)i, rates, statuses[i]);
    if (event == NULL) {
      riemann_message_free(msg);
      sfree(rates);
      return NULL;
    }
    riemann_message_append_events(msg, event, NULL);
  }

  sfree(rates);
  return msg;
}