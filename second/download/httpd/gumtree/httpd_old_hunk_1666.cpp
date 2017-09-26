    }

    ap_log_error(APLOG_MARK, APLOG_DEBUG, 0, s,
                 "proxy: %s: connection complete to %pI (%s)",
                 proxy_function, backend_addr, conn->hostname);

    /* set up the connection filters */
    rc = ap_run_pre_connection(conn->connection, conn->sock);
    if (rc != OK && rc != DONE) {
        conn->connection->aborted = 1;
        ap_log_error(APLOG_MARK, APLOG_DEBUG, 0, s,
                     "proxy: %s: pre_connection setup failed (%d)",
                     proxy_function, rc);
        return rc;
    }

    return OK;
}

int ap_proxy_lb_workers(void)
{
