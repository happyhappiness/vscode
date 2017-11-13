int SSLize_Socket(SOCKET socketHnd, char *key, request_rec *r)
{
    int rcode;
    struct tlsserveropts sWS2Opts;
    struct nwtlsopts    sNWTLSOpts;
    unicode_t SASKey[512];
    unsigned long ulFlag;
    
    memset((char *)&sWS2Opts, 0, sizeof(struct tlsserveropts));
    memset((char *)&sNWTLSOpts, 0, sizeof(struct nwtlsopts));
    
    
    ulFlag = SO_TLS_ENABLE;
    rcode = WSAIoctl(socketHnd, SO_TLS_SET_FLAGS, &ulFlag, sizeof(unsigned long), NULL, 0, NULL, NULL, NULL);
    if(rcode)
    {
        ap_log_error(APLOG_MARK, APLOG_ERR, 0, r->server,
                     "Error: %d with WSAIoctl(SO_TLS_SET_FLAGS, SO_TLS_ENABLE)", WSAGetLastError());
        goto ERR;
    }
    
    
    ulFlag = SO_TLS_SERVER;
    rcode = WSAIoctl(socketHnd, SO_TLS_SET_FLAGS, &ulFlag, sizeof(unsigned long),NULL, 0, NULL, NULL, NULL);
    
    if(rcode)
    {
        ap_log_error(APLOG_MARK, APLOG_ERR, 0, r->server,
                     "Error: %d with WSAIoctl(SO_TLS_SET_FLAGS, SO_TLS_SERVER)", WSAGetLastError());
        goto ERR;
    }
    
    loc2uni(UNI_LOCAL_DEFAULT, SASKey, key, 0, 0);

    //setup the tlsserveropts struct
    sWS2Opts.wallet = SASKey;
    sWS2Opts.walletlen = unilen(SASKey);
    sWS2Opts.sidtimeout = 0;
    sWS2Opts.sidentries = 0;
    sWS2Opts.siddir = NULL;
    sWS2Opts.options = &sNWTLSOpts;
    
    //setup the nwtlsopts structure
    
    sNWTLSOpts.walletProvider               = WAL_PROV_KMO;
    sNWTLSOpts.keysList                     = NULL;
    sNWTLSOpts.numElementsInKeyList         = 0;
    sNWTLSOpts.reservedforfutureuse         = NULL;
    sNWTLSOpts.reservedforfutureCRL         = NULL;
    sNWTLSOpts.reservedforfutureCRLLen      = NULL;
    sNWTLSOpts.reserved1                    = NULL;
    sNWTLSOpts.reserved2                    = NULL;
    sNWTLSOpts.reserved3                    = NULL;
    
    
    rcode = WSAIoctl(socketHnd, 
                     SO_TLS_SET_SERVER, 
                     &sWS2Opts, 
                     sizeof(struct tlsserveropts), 
                     NULL, 
                     0, 
                     NULL, 
                     NULL, 
                     NULL);
    if(SOCKET_ERROR == rcode) {
        ap_log_error(APLOG_MARK, APLOG_ERR, 0, r->server,
                     "Error: %d with WSAIoctl(SO_TLS_SET_SERVER)", WSAGetLastError());
        goto ERR;
    }
    
ERR:
    return rcode;
}