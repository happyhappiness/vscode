        ap_log_error(APLOG_MARK, APLOG_CRIT, status, s,
                     "Digest: error generating secret: %s",
                     apr_strerror(status, buf, sizeof(buf)));
        return status;
    }

    ap_log_error(APLOG_MARK, APLOG_NOTICE, 0, s, "Digest: done");

    return APR_SUCCESS;
}

static void log_error_and_cleanup(char *msg, apr_status_t sts, server_rec *s)
{
