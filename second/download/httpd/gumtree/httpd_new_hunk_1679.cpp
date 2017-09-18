			 DWORD dwReserved) {
    request_rec *r = ((isapi_cid *)ConnID)->r;
    int writ;	/* written, actually, but why shouldn't I make up words? */

    /* We only support synchronous writing */
    if (dwReserved && dwReserved != HSE_IO_SYNC) {
	ap_log_rerror(APLOG_MARK, APLOG_WARNING, r,
		    "ISAPI asynchronous I/O not supported: %s", r->filename);
	SetLastError(ERROR_INVALID_PARAMETER);
	return FALSE;
    }

    if ((writ = ap_rwrite(Buffer, *lpwdwBytes, r)) == EOF) {
