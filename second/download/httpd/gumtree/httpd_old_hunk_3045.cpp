        APR_BRIGADE_INSERT_TAIL(header_brigade, e);
    }
    /* This is all a single brigade, pass with flush flagged */
    return(pass_brigade(bucket_alloc, r, p_conn, origin, header_brigade, 1));
}

static
int ap_proxy_http_request(apr_pool_t *p, request_rec *r,
                                   proxy_conn_rec *p_conn, proxy_worker *worker,
                                   proxy_server_conf *conf,
                                   apr_uri_t *uri,
                                   char *url, char *server_portstr)
