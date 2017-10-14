static void log_error_and_cleanup(char *msg, apr_status_t sts, server_rec *s)
{
    ap_log_error(APLOG_MARK, APLOG_ERR, sts, s,
                 "Digest: %s - all nonce-count checking, one-time nonces, and "
                 "MD5-sess algorithm disabled", msg);

    cleanup_tables(NULL);
}