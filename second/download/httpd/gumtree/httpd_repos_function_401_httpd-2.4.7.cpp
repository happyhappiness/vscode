static const char *log_remote_address(request_rec *r, char *a)
{
    if (a && !strcmp(a, "c")) {
        return r->connection->client_ip;
    }
    else {
        return r->useragent_ip;
    }
}