static const char *log_pid_tid(request_rec *r, char *a)
{
    if (*a == '\0' || !strcasecmp(a, "pid")) {
        return ap_append_pid(r->pool, "", "");
    }
    else if (!strcasecmp(a, "tid") || !strcasecmp(a, "hextid")) {
#if APR_HAS_THREADS
        apr_os_thread_t tid = apr_os_thread_current();
#else
        int tid = 0; /* APR will format "0" anyway but an arg is needed */
#endif
        return apr_psprintf(r->pool,
#if APR_MAJOR_VERSION > 1 || (APR_MAJOR_VERSION == 1 && APR_MINOR_VERSION >= 2)
                            /* APR can format a thread id in hex */
                            *a == 'h' ? "%pt" : "%pT",
#else
                            /* APR is missing the feature, so always use decimal */
                            "%pT",
#endif
                            &tid);
    }
    /* bogus format */
    return a;
}