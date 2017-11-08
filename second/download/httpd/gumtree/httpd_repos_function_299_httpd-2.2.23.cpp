static apr_status_t dav_cleanup_liveprops(void *ctx)
{
    dav_liveprop_uris = NULL;
    dav_liveprop_count = 0;
    return APR_SUCCESS;
}