         */
        cid->r->status = old_status;
        cid->r->status_line = ap_get_status_line(cid->r->status);
        cid->ecb->dwHttpStatusCode = cid->r->status;
    }
    else {
        /* None of dwHttpStatusCode, the parser's r->status nor the 
         * old value of r->status were helpful, and nothing was decoded
         * from Status: string passed to us.  Let's just say HTTP_OK 
         * and get the data out, this was the isapi dev's oversight.
         */
        cid->r->status = HTTP_OK;
        cid->r->status_line = ap_get_status_line(cid->r->status);
        cid->ecb->dwHttpStatusCode = cid->r->status;
        ap_log_rerror(APLOG_MARK, APLOG_DEBUG, 0, cid->r,
                "ISAPI: Could not determine HTTP response code; using %d",
                cid->r->status);
    }

    if (cid->r->status == HTTP_INTERNAL_SERVER_ERROR) {
        return -1;
    }
