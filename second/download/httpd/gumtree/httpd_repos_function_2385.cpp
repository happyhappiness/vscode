static int noloris_conn(conn_rec *conn)
{
    struct { int child_num; int thread_num; } *sbh = conn->sbh;

    char *shm_rec;
    if (shm == NULL) {
        return DECLINED;  /* we're disabled */
    }

    /* check the IP is not banned */
    shm_rec = apr_shm_baseaddr_get(shm);
    while (shm_rec[0] != '\0') {
        if (!strcmp(shm_rec, conn->remote_ip)) {
            apr_socket_t *csd = ap_get_module_config(conn->conn_config, &core_module);
            ap_log_cerror(APLOG_MARK, APLOG_ERR, 0, conn,
                          "Dropping connection from banned IP %s",
                          conn->remote_ip);
            apr_socket_close(csd);

            return DONE;
        }
        shm_rec += ADDR_MAX_SIZE;
    }

    /* store this client IP for the monitor to pick up */
 
    ap_update_child_status_from_conn(conn->sbh, SERVER_READY, conn);

    return DECLINED;
}