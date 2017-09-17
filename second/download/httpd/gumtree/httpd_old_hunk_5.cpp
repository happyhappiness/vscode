
    /* Pass one --- direct matches */

    for (handp = handlers; handp->hr.content_type; ++handp) {
	if (handler_len == handp->len
	    && !strncmp(handler, handp->hr.content_type, handler_len)) {
            int result = (*handp->hr.handler) (r);

            if (result != DECLINED)
                return result;
        }
    }

    /* Pass two --- wildcard matches */

    for (handp = wildhandlers; handp->hr.content_type; ++handp) {
	if (handler_len >= handp->len
	    && !strncmp(handler, handp->hr.content_type, handp->len)) {
             int result = (*handp->hr.handler) (r);

             if (result != DECLINED)
                 return result;
         }
    }

