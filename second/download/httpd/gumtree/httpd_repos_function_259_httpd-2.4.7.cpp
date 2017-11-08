static apr_size_t dav_fs_append_uri(apr_pool_t *p, dav_buffer *pbuf,
                                    const char *path, apr_size_t pad)
{
    const char *epath = ap_escape_uri(p, path);
    apr_size_t epath_len = strlen(epath);

    dav_buffer_place_mem(p, pbuf, epath, epath_len + 1, pad);
    return epath_len;
}