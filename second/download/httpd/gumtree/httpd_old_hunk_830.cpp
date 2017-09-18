    else {
        cid->ecb->cbTotalBytes = 0;
        cid->ecb->cbAvailable = 0;
        cid->ecb->lpbData = NULL;
    }

    /* All right... try and run the sucker */
    rv = (*isa->HttpExtensionProc)(cid->ecb);

    /* Check for a log message - and log it */
    if (cid->ecb->lpszLogData && *cid->ecb->lpszLogData)
        ap_log_rerror(APLOG_MARK, APLOG_INFO, 0, r,
