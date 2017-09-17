
	if (cid->status) /* We have a special status to return */
	    return cid->status;

	return OK;
    case HSE_STATUS_PENDING:	/* We don't support this */
	ap_log_error(APLOG_MARK, APLOG_WARNING, r->server,
		    "ISAPI asynchronous I/O not supported: %s", r->filename);
    case HSE_STATUS_ERROR:
    default:
	return SERVER_ERROR;
    }

