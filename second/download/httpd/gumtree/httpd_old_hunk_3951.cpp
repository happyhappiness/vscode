            if (r->args)
                r->args = apr_pstrcat(r->pool, r->args, (char*) buf_data, NULL);
            else
                r->args = apr_pstrdup(r->pool, (char*) buf_data);
        }
        if (cid->dconf.log_to_errlog)
            ap_log_rerror(APLOG_MARK, APLOG_INFO, 0, r,
                          "%s: %s", cid->r->filename,
                          (char*) buf_data);
        return 1;

    case HSE_REQ_IO_COMPLETION:
        /* Emulates a completion port...  Record callback address and
