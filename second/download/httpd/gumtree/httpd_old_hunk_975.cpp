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

