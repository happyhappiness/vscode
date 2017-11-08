static int same_authority(const h2_request *req, const apr_uri_t *uri)
{
    if (uri->scheme != NULL && strcmp(uri->scheme, req->scheme)) {
        return 0;
    }
    if (uri->hostinfo != NULL && strcmp(uri->hostinfo, req->authority)) {
        return 0;
    }
    return 1;
}