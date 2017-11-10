static const char *log_requests_on_connection(request_rec *r, char *a)
{
    int num = r->connection->keepalives ? r->connection->keepalives - 1 : 0;
    return apr_itoa(r->pool, num);
}