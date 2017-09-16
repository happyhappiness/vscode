        else {

            /*

             * Dumb user has given us a bad url to redirect to --- fake up

             * dying with a recursive server error...

             */

            recursive_error = SERVER_ERROR;

            ap_log_error(APLOG_MARK, APLOG_NOERRNO|APLOG_ERR, r->server,

                        "Invalid error redirection directive: %s",

                        custom_response);

        }

    }

    ap_send_error_response(r, recursive_error);

}



static void decl_die(int status, char *phase, request_rec *r)

{

    if (status == DECLINED) {

        ap_log_error(APLOG_MARK, APLOG_NOERRNO|APLOG_CRIT, r->server,

                    "configuration error:  couldn't %s: %s", phase, r->uri);

        ap_die(SERVER_ERROR, r);

    }

    else

        ap_die(status, r);

}

