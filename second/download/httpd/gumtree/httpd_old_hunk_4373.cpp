        p_conn->worker->s->transferred += transferred;
    status = ap_pass_brigade(origin->output_filters, bb);
    /* Cleanup the brigade now to avoid buckets lifetime
     * issues in case of error returned below. */
    apr_brigade_cleanup(bb);
    if (status != APR_SUCCESS) {
        ap_log_cerror(APLOG_MARK, APLOG_ERR, status, origin, APLOGNO(03357)
                      "pass output failed to %pI (%s)",
                      p_conn->addr, p_conn->hostname);
    }
    return status;
}

