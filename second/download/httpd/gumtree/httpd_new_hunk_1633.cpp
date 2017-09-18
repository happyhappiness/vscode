		    encoding_len++;
		    continue;
		}
		else {
		    /* should not be possible */
		    /* abandon malfunctioning module */
		    ap_log_rerror(APLOG_MARK, APLOG_NOERRNO | APLOG_ERR, r,
				MODNAME ": bad state %d (ns)", state);
		    return DECLINED;
		}
		/* NOTREACHED */
	    }
	    /* NOTREACHED */
