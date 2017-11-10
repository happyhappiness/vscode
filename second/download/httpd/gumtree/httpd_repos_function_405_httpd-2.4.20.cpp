static const char *log_local_address(request_rec *r, char *a)
{
    return r->connection->local_ip;
}