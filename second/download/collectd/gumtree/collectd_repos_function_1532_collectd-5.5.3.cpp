static int ceph_cb_string(void *ctx, const unsigned char *string_val,
        yajl_len_t string_len)
{
    return CEPH_CB_CONTINUE;
}