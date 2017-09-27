}

static apr_status_t initialize_secret(server_rec *s)
{
    apr_status_t status;

    ap_log_error(APLOG_MARK, APLOG_DEBUG, 0, s, APLOGNO(01757)
                 "generating secret for digest authentication ...");

#if APR_HAS_RANDOM
    status = apr_generate_random_bytes(secret, sizeof(secret));
#else
#error APR random number support is missing; you probably need to install the truerand library.
