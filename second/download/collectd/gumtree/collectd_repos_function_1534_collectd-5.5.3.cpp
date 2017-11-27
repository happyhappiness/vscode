static int ceph_cb_end_map(void *ctx)
{
    yajl_struct *state = (yajl_struct*) ctx;

    /* Pop key from the stack */
    if (state->depth == 0)
        return CEPH_CB_ABORT;

    sfree (state->key);
    state->depth--;
    state->key = state->stack[state->depth];
    state->stack[state->depth] = NULL;

    return CEPH_CB_CONTINUE;
}