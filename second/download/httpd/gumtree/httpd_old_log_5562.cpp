E(int) ap_rputs(const char *str, request_rec *r)
{
    apr_size_t len;

    if (r->connection->aborted)
        return -1;;