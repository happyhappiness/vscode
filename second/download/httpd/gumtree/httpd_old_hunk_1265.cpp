        return 0;
    else
        return 1;
}
#endif /* USE_ALTERNATE_IS_CONNECTED */

PROXY_DECLARE(int) ap_proxy_connect_backend(const char *proxy_function,
                                            proxy_conn_rec *conn,
                                            proxy_worker *worker,
                                            server_rec *s)
{
    apr_status_t rv;
