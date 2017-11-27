static int ceph_cb_number(void *ctx, const char *number_val,
                          yajl_len_t number_len) {
  yajl_struct *state = (yajl_struct *)ctx;
  char buffer[number_len + 1];
  char key[2 * DATA_MAX_NAME_LEN] = {0};
  _Bool latency_type = 0;
  int status;

  memcpy(buffer, number_val, number_len);
  buffer[sizeof(buffer) - 1] = '\0';

  for (size_t i = 0; i < state->depth; i++) {
    if (state->stack[i] == NULL)
      continue;

    if (strlen(key) != 0)
      BUFFER_ADD(key, ".");
    BUFFER_ADD(key, state->stack[i]);
  }

  /* Special case for latency metrics. */
  if ((strcmp("avgcount", state->key) == 0) ||
      (strcmp("sum", state->key) == 0)) {
    latency_type = 1;

    /* depth >= 2  =>  (stack[-1] != NULL && stack[-2] != NULL) */
    assert((state->depth < 2) || ((state->stack[state->depth - 1] != NULL) &&
                                  (state->stack[state->depth - 2] != NULL)));

    /* Super-special case for filestore.journal_wr_bytes.avgcount: For
     * some reason, Ceph schema encodes this as a count/sum pair while all
     * other "Bytes" data (excluding used/capacity bytes for OSD space) uses
     * a single "Derive" type. To spare further confusion, keep this KPI as
     * the same type of other "Bytes". Instead of keeping an "average" or
     * "rate", use the "sum" in the pair and assign that to the derive
     * value. */
    if (convert_special_metrics && (state->depth >= 2) &&
        (strcmp("filestore", state->stack[state->depth - 2]) == 0) &&
        (strcmp("journal_wr_bytes", state->stack[state->depth - 1]) == 0) &&
        (strcmp("avgcount", state->key) == 0)) {
      DEBUG("ceph plugin: Skipping avgcount for filestore.JournalWrBytes");
      return CEPH_CB_CONTINUE;
    }
  } else /* not a latency type */
  {
    BUFFER_ADD(key, ".");
    BUFFER_ADD(key, state->key);
  }

  status = state->handler(state->handler_arg, buffer, key);
  if ((status == RETRY_AVGCOUNT) && latency_type) {
    /* Add previously skipped part of the key, either "avgcount" or "sum",
     * and try again. */
    BUFFER_ADD(key, ".");
    BUFFER_ADD(key, state->key);

    status = state->handler(state->handler_arg, buffer, key);
  }

  if (status != 0) {
    ERROR("ceph plugin: JSON handler failed with status %d.", status);
    return CEPH_CB_ABORT;
  }

  return CEPH_CB_CONTINUE;
}