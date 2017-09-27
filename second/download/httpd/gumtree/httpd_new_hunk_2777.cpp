        else {
            /*
             * Dumb user has given us a bad url to redirect to --- fake up
             * dying with a recursive server error...
             */
            recursive_error = HTTP_INTERNAL_SERVER_ERROR;
            ap_log_rerror(APLOG_MARK, APLOG_ERR, 0, r, APLOGNO(01580)
                        "Invalid error redirection directive: %s",
                        custom_response);
        }
    }
    ap_send_error_response(r_1st_err, recursive_error);
}
