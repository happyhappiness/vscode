        } else {
            ap_log_error(APLOG_MARK, APLOG_DEBUG, 0, r->server,
                         "proxy: header only");
        }
    }

    if ( conf->error_override ) {
        /* the code above this checks for 'OK' which is what the hook expects */
        if ( r->status == HTTP_OK )
            return OK;
        else  {
            /* clear r->status for override error, otherwise ErrorDocument
