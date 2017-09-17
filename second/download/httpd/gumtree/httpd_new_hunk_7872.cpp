		errstr[len-1] = ' ';
	    }
	}
    }
#endif

    len += ap_vsnprintf(errstr + len, sizeof(errstr) - len, fmt, args);

    /* NULL if we are logging to syslog */
    if (logf) {
	fputs(errstr, logf);
	fputc('\n', logf);
	fflush(logf);
