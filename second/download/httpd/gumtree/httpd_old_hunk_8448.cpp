		errstr[len-1] = ' ';
	    }
	}
    }
#endif

    va_start(args, fmt);
    len += ap_vsnprintf(errstr + len, sizeof(errstr) - len, fmt, args);
    va_end(args);

    /* NULL if we are logging to syslog */
    if (logf) {
	fputs(errstr, logf);
	fputc('\n', logf);
	fflush(logf);
