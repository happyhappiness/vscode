static int
ceph_cb_map_key(void *ctx, const unsigned char *key, yajl_len_t string_len)
{
    yajl_struct *state = (yajl_struct*) ctx;
    size_t sz = ((size_t) string_len) + 1;

    sfree (state->key);
    state->key = malloc (sz);
    if (state->key == NULL)
    {
        ERROR ("ceph plugin: malloc failed.");
        return CEPH_CB_ABORT;
    }

    memmove (state->key, key, sz - 1);
    state->key[sz - 1] = 0;

    return CEPH_CB_CONTINUE;
}