        /* Zap leading whitespace by shifting */
        if (src != buf)
	    for (dst = buf; (*dst++ = *src++) != '\0'; )
	        ;

#ifdef DEBUG_CFG_LINES
	ap_log_error(APLOG_MARK, APLOG_DEBUG|APLOG_NOERRNO, 0, NULL, "Read config: %s", buf);
#endif
	return 0;
    } else {
	/* No "get string" function defined; read character by character */
	register int c;
	register size_t i = 0;
