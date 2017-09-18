     * persistent connections and Nagle's algorithm that have very severe
     * performance penalties.  (Failing to disable Nagle is not much of a
     * problem with simple HTTP.)
     *
     * In spite of these problems, failure here is not a shooting offense.
     */
    apr_status_t status = apr_setsocketopt(s, APR_TCP_NODELAY, 1);

    if (status != APR_SUCCESS) {
        ap_log_error(APLOG_MARK, APLOG_WARNING, status, ap_server_conf,
                     "setsockopt: (TCP_NODELAY)");
    }
}
#endif

#ifdef HAVE_GETPWNAM
AP_DECLARE(uid_t) ap_uname2id(const char *name)
