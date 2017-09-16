    /* Set the status (for logging) */

    if (ecb->dwHttpStatusCode)

	r->status = ecb->dwHttpStatusCode;



    /* Check for a log message - and log it */

    if (ecb->lpszLogData && strcmp(ecb->lpszLogData, ""))

	ap_log_rerror(APLOG_MARK, APLOG_ERR, r,

		    "%s: %s", ecb->lpszLogData, r->filename);



    /* All done with the DLL... get rid of it */

    if (isapi_term) (*isapi_term)(HSE_TERM_MUST_UNLOAD);

    FreeLibrary(isapi_handle);



