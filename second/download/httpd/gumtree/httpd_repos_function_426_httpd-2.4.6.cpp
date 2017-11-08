static const char *log_server_port(request_rec *r, char *a)
{
    apr_port_t port;

    if (*a == '\0' || !strcasecmp(a, "canonical")) {
        port = r->server->port ? r->server->port : ap_default_port(r);
    }
    else if (!strcasecmp(a, "remote")) {
        port = r->useragent_addr->port;
    }
    else if (!strcasecmp(a, "local")) {
        port = r->connection->local_addr->port;
    }
    else {
        /* bogus format */
        return a;
    }
    return apr_itoa(r->pool, (int)port);
}