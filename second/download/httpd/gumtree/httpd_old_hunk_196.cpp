        additional = atoi(&code[1]) * APR_USEC_PER_SEC;
        break;
    default:
        /* expecting the add_* routines to be case-hardened this 
         * is just a reminder that module is beta
         */
        ap_log_rerror(APLOG_MARK, APLOG_NOERRNO|APLOG_ERR, 0, r,
                    "internal error: bad expires code: %s", r->filename);
        return HTTP_INTERNAL_SERVER_ERROR;
    }

    expires = base + additional;
    apr_table_mergen(r->headers_out, "Cache-Control",
