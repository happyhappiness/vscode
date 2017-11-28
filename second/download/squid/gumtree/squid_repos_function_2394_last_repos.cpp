void
HttpRequest::init()
{
    method = Http::METHOD_NONE;
    url.clear();
#if USE_AUTH
    auth_user_request = NULL;
#endif
    memset(&flags, '\0', sizeof(flags));
    range = NULL;
    ims = -1;
    imslen = 0;
    lastmod = -1;
    client_addr.setEmpty();
    my_addr.setEmpty();
    body_pipe = NULL;
    // hier
    dnsWait = -1;
    errType = ERR_NONE;
    errDetail = ERR_DETAIL_NONE;
    peer_login = NULL;      // not allocated/deallocated by this class
    peer_domain = NULL;     // not allocated/deallocated by this class
    peer_host = NULL;
    vary_headers = SBuf();
    myportname = null_string;
    tag = null_string;
#if USE_AUTH
    extacl_user = null_string;
    extacl_passwd = null_string;
#endif
    extacl_log = null_string;
    extacl_message = null_string;
    pstate = psReadyToParseStartLine;
#if FOLLOW_X_FORWARDED_FOR
    indirect_client_addr.setEmpty();
#endif /* FOLLOW_X_FORWARDED_FOR */
#if USE_ADAPTATION
    adaptHistory_ = NULL;
#endif
#if ICAP_CLIENT
    icapHistory_ = NULL;
#endif
    rangeOffsetLimit = -2; //a value of -2 means not checked yet
    forcedBodyContinuation = false;
}