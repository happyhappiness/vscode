		}
		/* blast trailing whitespace */
		while (i > 0 && apr_isspace(buf[i - 1]))
		    --i;
		buf[i] = '\0';
#ifdef DEBUG_CFG_LINES
		ap_log_error(APLOG_MARK, APLOG_DEBUG, 0, NULL, "Read config: %s", buf);
#endif
		return 0;
	    }
	    buf[i] = c;
	    ++i;
	    c = cfp->getch(cfp->param);
