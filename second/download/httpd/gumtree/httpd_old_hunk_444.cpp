		    /* else nothing needs be done because

		     * then the backslash is escaped and

		     * we just strip to a single one

		     */

		}

		/* blast trailing whitespace */

		while (i > 0 && isspace(buf[i - 1]))

		    --i;

		buf[i] = '\0';

#ifdef DEBUG_CFG_LINES

		ap_log_error(APLOG_MARK, APLOG_DEBUG|APLOG_NOERRNO, NULL, "Read config: %s", buf);

#endif

		return 0;

