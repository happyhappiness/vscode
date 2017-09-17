	        while ((*getsfunc) (w, MAX_STRING_LEN - 1, getsfunc_data)) {
		    continue;
		}
	    }

	    ap_kill_timeout(r);
	    ap_log_rerror(APLOG_MARK, APLOG_NOERRNO|APLOG_ERR, r,
			  "%s: %s", malformed, r->filename);
	    ap_table_setn(r->notes, "error-notes",
			  ap_pstrdup(r->pool, malformed));
	    return HTTP_INTERNAL_SERVER_ERROR;
	}

	*l++ = '\0';
	while (*l && ap_isspace(*l)) {
	    ++l;
	}
