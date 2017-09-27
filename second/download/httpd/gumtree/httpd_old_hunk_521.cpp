        }
        if (cid->dconf.log_to_errlog)
            ap_log_rerror(APLOG_MARK, APLOG_INFO, 0, r,
                          "ISAPI: %s: %s", cid->r->filename,
                          (char*) buf_data);
        return 1;
        
    case HSE_REQ_IO_COMPLETION:
        /* Emulates a completion port...  Record callback address and 
         * user defined arg, we will call this after any async request 
         * (e.g. transmitfile) as if the request executed async.
         * Per MS docs... HSE_REQ_IO_COMPLETION replaces any prior call
         * to HSE_REQ_IO_COMPLETION, and buf_data may be set to NULL.
         */
        if (cid->dconf.fake_async) {
            cid->completion = (PFN_HSE_IO_COMPLETION) buf_data;
