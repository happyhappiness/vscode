	    /* file doesn't exist on disk, so we can't do anything based on
	     * modification time.  Note that this does _not_ log an error.
	     */
	    return DECLINED;
	}
	base = r->finfo.mtime;
        additional = atoi(&code[1]) * APR_USEC_PER_SEC;
        break;
    case 'A':
        /* there's been some discussion and it's possible that 
         * 'access time' will be stored in request structure
         */
        base = r->request_time;
        additional = atoi(&code[1]) * APR_USEC_PER_SEC;
        break;
    default:
        /* expecting the add_* routines to be case-hardened this 
         * is just a reminder that module is beta
         */
        ap_log_rerror(APLOG_MARK, APLOG_ERR, 0, r,
                    "internal error: bad expires code: %s", r->filename);
        return HTTP_INTERNAL_SERVER_ERROR;
    }

    expires = base + additional;
    apr_table_mergen(r->headers_out, "Cache-Control",
		    apr_psprintf(r->pool, "max-age=%qd",
				(expires - r->request_time)
				    / APR_USEC_PER_SEC));
    timestr = apr_palloc(r->pool, APR_RFC822_DATE_LEN);
    apr_rfc822_date(timestr, expires);
    apr_table_setn(r->headers_out, "Expires", timestr);
    return OK;
}

