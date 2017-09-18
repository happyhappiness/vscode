		    data = lf + 1;	/* Reset data */
		break;
	    }

	    if (!(value = strchr(data, ':'))) {
		SetLastError(ERROR);	/* XXX: Find right error */
		ap_log_error(APLOG_MARK, APLOG_ERR, r->server,
			    "ISA sent invalid headers", r->filename);
		return FALSE;
	    }

	    *value++ = '\0';
	    while (*value && ap_isspace(*value)) ++value;
