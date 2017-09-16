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

-- apache_1.3.1/src/os/win32/modules.c	1998-04-11 20:01:06.000000000 +0800

