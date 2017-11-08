static apr_status_t inspect_clen(h2_request *req, const char *s)
{
    char *end;
    req->content_length = apr_strtoi64(s, &end, 10);
    return (s == end)? APR_EINVAL : APR_SUCCESS;
}