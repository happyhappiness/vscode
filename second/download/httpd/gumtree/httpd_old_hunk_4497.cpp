            r->server = s;
            return;
        }
    }
}


AP_DECLARE(void) ap_update_vhost_from_headers(request_rec *r)
{
    /* must set this for HTTP/1.1 support */
    if (r->hostname || (r->hostname = apr_table_get(r->headers_in, "Host"))) {
        fix_hostname(r);
        if (r->status != HTTP_OK)
            return;
    }
    /* check if we tucked away a name_chain */
    if (r->connection->vhost_lookup_data) {
        if (r->hostname)
            check_hostalias(r);
        else
            check_serverpath(r);
