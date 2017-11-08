static const char *header_request_ssl_var(request_rec *r, char *name)
{
    if (header_ssl_lookup) {
        const char *val = header_ssl_lookup(r->pool, r->server,
                                            r->connection, r, name);
        if (val && val[0])
            return unwrap_header(r->pool, val);
        else
            return "(null)";
    }
    else {
        return "(null)";
    }
}