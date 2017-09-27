        rv = HTTP_INTERNAL_SERVER_ERROR ;
        break;
    }

    if (rv != OK) {
        /* apr_status_t value has been logged in lower level method */
        ap_log_error(APLOG_MARK, APLOG_ERR, 0, r->server,
                     "proxy: pass request body failed to %pI (%s)"
                     " from %s (%s)",
                     p_conn->addr,
                     p_conn->hostname ? p_conn->hostname: "",
                     c->remote_ip,
                     c->remote_host ? c->remote_host: "");
        return rv;
    }

    return OK;
}

static void process_proxy_header(request_rec *r, proxy_dir_conf *c,
                                 const char *key, const char *value)
{
    static const char *date_hdrs[]
        = { "Date", "Expires", "Last-Modified", NULL };
    static const struct {
