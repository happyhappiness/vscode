static apr_status_t recall_headers(cache_handle_t *h, request_rec *r)
{
    /* we recalled the headers during open_entity, so do nothing */
    return APR_SUCCESS;
}