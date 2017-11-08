static void closed_connection(serf_connection_t *conn,
                              void *closed_baton,
                              apr_status_t why,
                              apr_pool_t *pool)
{
    s_baton_t *ctx = closed_baton;

    if (why) {
        /* justin says that error handling isn't done yet. hah. */
        /* XXXXXX: review */
        ap_log_rerror(APLOG_MARK, APLOG_ERR, why, ctx->r, "Closed Connection Error");
        ctx->rstatus = HTTP_INTERNAL_SERVER_ERROR;
    }

    if (mpm_supprts_serf) {
        ap_mpm_register_timed_callback(apr_time_from_msec(1),
                                       timed_cleanup_callback, ctx);
    }
    ctx->keep_reading = 0;
}