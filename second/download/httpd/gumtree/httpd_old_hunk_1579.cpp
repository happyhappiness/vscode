     */
    ap_log_error(APLOG_MARK, APLOG_ERR, err, r->server, "%s", description);
}

static int cgid_server(void *data)
{
    struct sockaddr_un unix_addr;
    int sd, sd2, rc;
    mode_t omask;
    apr_socklen_t len;
    apr_pool_t *ptrans;
    server_rec *main_server = data;
    apr_hash_t *script_hash = apr_hash_make(pcgi);
    apr_status_t rv;

    apr_pool_create(&ptrans, pcgi);
