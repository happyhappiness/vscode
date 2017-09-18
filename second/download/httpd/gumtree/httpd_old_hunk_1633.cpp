		    encoding_len++;
		    continue;
		}
		else {
		    /* should not be possible */
		    /* abandon malfunctioning module */
		    ap_log_error(APLOG_MARK, APLOG_NOERRNO | APLOG_ERR, r->server,
				MODNAME ": bad state %d (ns)", state);
		    return DECLINED;
		}
		/* NOTREACHED */
	    }
	    /* NOTREACHED */
