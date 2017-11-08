static int ssl_hook_process_connection(conn_rec* c)
{
    SSLConnRec *sslconn = myConnConfig(c);

    if (sslconn && !sslconn->disabled) {
        /* On an active SSL connection, let the input filters initialize
         * themselves which triggers the handshake, which again triggers
         * all kinds of useful things such as SNI and ALPN.
         */
        apr_bucket_brigade* temp;

        temp = apr_brigade_create(c->pool, c->bucket_alloc);
        ap_get_brigade(c->input_filters, temp,
                       AP_MODE_INIT, APR_BLOCK_READ, 0);
        apr_brigade_destroy(temp);
    }
    
    return DECLINED;
}