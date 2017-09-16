    if (r->assbackwards && r->header_only) {

        /*

         * Client asked for headers only with HTTP/0.9, which doesn't send

         * headers!  Have to dink things even to make sure the error message

         * comes through...

         */

        ap_log_error(APLOG_MARK, APLOG_NOERRNO|APLOG_ERR, r->server,

                    "client sent illegal HTTP/0.9 request: %s", r->uri);

        r->header_only = 0;

        ap_die(BAD_REQUEST, r);

        return;

    }



