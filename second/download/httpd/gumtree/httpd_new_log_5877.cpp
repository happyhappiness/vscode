r(APLOG_MARK, APLOG_TRACE2, 0, s,
                 "Inter-Process Session Cache: "
                 "request=%s status=%s id=%s %s(session %s)",
                 request, status,
                 modssl_SSL_SESSION_id2sz(id, idlen, buf, sizeof(buf)),
                 timeout_str, result);