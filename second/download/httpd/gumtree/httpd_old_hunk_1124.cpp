	        while ((*getsfunc) (w, MAX_STRING_LEN - 1, getsfunc_data)) {

		    continue;

		}

	    }



	    ap_kill_timeout(r);

	    ap_log_error(APLOG_MARK, APLOG_NOERRNO|APLOG_ERR, r->server,

			 "%s: %s", malformed, r->filename);

	    return SERVER_ERROR;

	}



	*l++ = '\0';

	while (*l && ap_isspace(*l)) {

	    ++l;

	}

