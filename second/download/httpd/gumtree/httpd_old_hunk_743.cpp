     * Make really sure that when a peer certificate
     * is required we really got one... (be paranoid)
     */
    if ((sc->server->auth.verify_mode == SSL_CVERIFY_REQUIRE) &&
        !sslconn->client_cert)
    {
        ap_log_error(APLOG_MARK, APLOG_INFO, 0, c->base_server,
                     "No acceptable peer certificate available");

        return ssl_filter_io_shutdown(filter_ctx, c, 1);
    }

    return APR_SUCCESS;
}

static apr_status_t ssl_io_filter_input(ap_filter_t *f,
                                        apr_bucket_brigade *bb,
                                        ap_input_mode_t mode,
                                        apr_read_type_e block,
                                        apr_off_t readbytes)
{
