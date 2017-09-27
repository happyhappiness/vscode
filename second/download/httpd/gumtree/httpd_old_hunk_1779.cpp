                            const char *result,
                            long timeout)
{
    char buf[SSL_SESSION_ID_STRING_LEN];
    char timeout_str[56] = {'\0'};

    if (s->loglevel < APLOG_DEBUG) {
        return;
    }

    if (timeout) {
        apr_snprintf(timeout_str, sizeof(timeout_str),
                     "timeout=%lds ", (timeout - time(NULL)));
    }

    ap_log_error(APLOG_MARK, APLOG_DEBUG, 0, s,
                 "Inter-Process Session Cache: "
                 "request=%s status=%s id=%s %s(session %s)",
                 request, status,
                 SSL_SESSION_id2sz(id, idlen, buf, sizeof(buf)),
                 timeout_str, result);
}
