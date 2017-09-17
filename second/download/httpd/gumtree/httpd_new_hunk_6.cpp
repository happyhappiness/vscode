
    /* Pass one --- direct matches */

    for (handp = handlers; handp->hr.content_type; ++handp) {
	if (handler_len == handp->len
	    && !strncmp(handler, handp->hr.content_type, handler_len)) {
            result = (*handp->hr.handler) (r);

            if (result != DECLINED)
                return result;
        }
    }

    if (result == NOT_IMPLEMENTED && r->handler) {
        ap_log_error(APLOG_MARK, APLOG_NOERRNO|APLOG_WARNING, r->server,
            "handler \"%s\" not found for: %s", r->handler, r->filename);
    }

    /* Pass two --- wildcard matches */

    for (handp = wildhandlers; handp->hr.content_type; ++handp) {
	if (handler_len >= handp->len
	    && !strncmp(handler, handp->hr.content_type, handp->len)) {
             result = (*handp->hr.handler) (r);

             if (result != DECLINED)
                 return result;
         }
    }

