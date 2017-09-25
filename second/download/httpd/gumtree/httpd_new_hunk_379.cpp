
    return APR_SUCCESS;
}

static apr_status_t ssl_io_filter_cleanup(void *data)
{
    ssl_filter_ctx_t *filter_ctx = data;

    if (filter_ctx->pssl) {
        conn_rec *c = (conn_rec *)SSL_get_app_data(filter_ctx->pssl);
        SSLConnRec *sslconn = myConnConfig(c);

        ap_log_error(APLOG_MARK, APLOG_DEBUG, 0, NULL,
                     "SSL connection destroyed without being closed");

        SSL_free(filter_ctx->pssl);
        sslconn->ssl = filter_ctx->pssl = NULL;
    }
  
    return APR_SUCCESS;
}

/*
 * The hook is NOT registered with ap_hook_process_connection. Instead, it is
 * called manually from the churn () before it tries to read any data.
 * There is some problem if I accept conn_rec *. Still investigating..
