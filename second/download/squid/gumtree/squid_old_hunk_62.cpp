    HttpRequest *request = checklist->request;
    http_hdr_type headertype;

    if (NULL == request) {
        fatal ("requiresRequest SHOULD have been true for this ACL!!");
        return 0;
    } else if (request->flags.accelerated) {
        /* WWW authorization on accelerated requests */
        headertype = HDR_AUTHORIZATION;
    } else if (request->flags.intercepted || request->flags.spoof_client_ip) {
        debugs(28, DBG_IMPORTANT, HERE << " authentication not applicable on intercepted requests.");
        return -1;
