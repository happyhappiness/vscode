static const char *log_remote_address(request_rec *r, char *a)
{
    return r->connection->remote_ip;
}