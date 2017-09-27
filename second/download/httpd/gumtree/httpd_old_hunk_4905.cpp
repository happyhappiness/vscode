        return errstatus;
    }

    if (r->method_number == M_GET || r->method_number == M_POST) {
        if (r->finfo.filetype == APR_NOFILE) {
            ap_log_rerror(APLOG_MARK, APLOG_INFO, 0, r, APLOGNO(00128)
                          "File does not exist: %s", r->filename);
            return HTTP_NOT_FOUND;
        }

        /* Don't try to serve a dir.  Some OSs do weird things with
         * raw I/O on a dir.
         */
