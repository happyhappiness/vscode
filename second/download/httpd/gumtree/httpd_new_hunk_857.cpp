    }
    else {
        if (type == REMOTE_HOST || type == REMOTE_DOUBLE_REV) {
            return NULL;
        }
        else {
            *str_is_ip = 1;
            return conn->remote_ip;
        }
    }
}

/*
 * Optional function coming from mod_ident, used for looking up ident user
 */
static APR_OPTIONAL_FN_TYPE(ap_ident_lookup) *ident_lookup;

AP_DECLARE(const char *) ap_get_remote_logname(request_rec *r)
{
    if (r->connection->remote_logname != NULL) {
        return r->connection->remote_logname;
    }

    if (ident_lookup) {
        return ident_lookup(r);
    }

    return NULL;
}

/* There are two options regarding what the "name" of a server is.  The
 * "canonical" name as defined by ServerName and Port, or the "client's
 * name" as supplied by a possible Host: header or full URI.
 *
 * The DNS option to UseCanonicalName causes this routine to do a
 * reverse lookup on the local IP address of the connection and use
 * that for the ServerName. This makes its value more reliable while
 * at the same time allowing Demon's magic virtual hosting to work.
 * The assumption is that DNS lookups are sufficiently quick...
 * -- fanf 1998-10-03
 */
AP_DECLARE(const char *) ap_get_server_name(request_rec *r)
{
    conn_rec *conn = r->connection;
    core_dir_config *d;
    const char *retval;

    d = (core_dir_config *)ap_get_module_config(r->per_dir_config,
                                                &core_module);

    switch (d->use_canonical_name) {
        case USE_CANONICAL_NAME_ON:
            retval = r->server->server_hostname;
            break;
        case USE_CANONICAL_NAME_DNS:
            if (conn->local_host == NULL) {
                if (apr_getnameinfo(&conn->local_host,
                                conn->local_addr, 0) != APR_SUCCESS)
                    conn->local_host = apr_pstrdup(conn->pool,
                                               r->server->server_hostname);
                else {
                    ap_str_tolower(conn->local_host);
                }
            }
            retval = conn->local_host;
            break;
        case USE_CANONICAL_NAME_OFF:
        case USE_CANONICAL_NAME_UNSET:
            retval = r->hostname ? r->hostname : r->server->server_hostname;
            break;
        default:
            ap_log_rerror(APLOG_MARK, APLOG_ERR, 0, r,
                         "ap_get_server_name: Invalid UCN Option somehow");
            retval = "localhost";
            break;
    }
    return retval;
}

/*
 * Get the current server name from the request for the purposes
 * of using in a URL.  If the server name is an IPv6 literal
 * address, it will be returned in URL format (e.g., "[fe80::1]").
