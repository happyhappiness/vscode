	 */
	return TRUE;

    /* We don't support all this async I/O, Microsoft-specific stuff */
    case HSE_REQ_IO_COMPLETION:
    case HSE_REQ_TRANSMIT_FILE:
	ap_log_error(APLOG_MARK, APLOG_WARNING, r->server,
		    "ISAPI asynchronous I/O not supported: %s", r->filename);
    default:
	SetLastError(ERROR_INVALID_PARAMETER);
	return FALSE;
    }
}
