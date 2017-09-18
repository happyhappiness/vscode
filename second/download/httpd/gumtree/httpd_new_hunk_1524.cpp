		    }   
		}
	    }
	    break;
	}

	/*
	 * Leading and trailing white space is eliminated completely
	 */
	src = buf;
	while (ap_isspace(*src))
	    ++src;
	/* blast trailing whitespace */
	dst = &src[strlen(src)];
	while (--dst >= src && ap_isspace(*dst))
	    *dst = '\0';
        /* Zap leading whitespace by shifting */
        if (src != buf)
	    for (dst = buf; (*dst++ = *src++) != '\0'; )
	        ;

#ifdef DEBUG_CFG_LINES
	ap_log_error(APLOG_MARK, APLOG_DEBUG|APLOG_NOERRNO, NULL, "Read config: %s", buf);
#endif
	return 0;
    } else {
