static int ceph_cb_start_map(void *ctx) {
  yajl_struct *state = (yajl_struct *)ctx;

  /* Push key to the stack */
  if (state->depth == YAJL_MAX_DEPTH)
    return CEPH_CB_ABORT;

  state->stack[state->depth] = state->key;
  state->depth++;
  state->key = NULL;

  return CEPH_CB_CONTINUE;
}