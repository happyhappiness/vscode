void
HttpRequest::init()
{
    method = METHOD_NONE;
    protocol = AnyP::PROTO_NONE;
    urlpath = NULL;
    login[0] = '\0';
    host[0] = '\0';
    host_is_numeric = -1;
#if USE_AUTH
    auth_user_request = NULL;
#endif
    port = 0;
    canonical = NULL;
    memset(&flags, '\0', sizeof(flags));
    range = NULL;
    ims = -1;
    imslen = 0;
    lastmod = -1;
    client_addr.SetEmpty();
    my_addr.SetEmpty();
    body_pipe = NULL;
    // hier
    dnsWait = -1;
    errType = ERR_NONE;
    errDetail = ERR_DETAIL_NONE;
    peer_login = NULL;		// not allocated/deallocated by this class
    peer_domain = NULL;		// not allocated/deallocated by this class
    vary_headers = NULL;
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
    indirect_client_addr.SetEmpty();
#endif /* FOLLOW_X_FORWARDED_FOR */
#if USE_ADAPTATION
    adaptHistory_ = NULL;
#endif
#if ICAP_CLIENT
    icapHistory_ = NULL;
#endif
    rangeOffsetLimit = -2; //a value of -2 means not checked yet
}