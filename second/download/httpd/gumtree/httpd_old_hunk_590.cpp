		/* Soak up all the script output - may save an outright kill */
	        while ((*getsfunc) (w, MAX_STRING_LEN - 1, getsfunc_data)) {
		    continue;
		}
	    }

	    ap_log_rerror(APLOG_MARK, APLOG_NOERRNO|APLOG_ERR|APLOG_TOCLIENT, 0, r,
			  "%s: %s", malformed, 
                          apr_filename_of_pathname(r->filename));
	    return HTTP_INTERNAL_SERVER_ERROR;
	}

	*l++ = '\0';
