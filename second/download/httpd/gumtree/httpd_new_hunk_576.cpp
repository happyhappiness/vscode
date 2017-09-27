                         "(SO_SSL_SET_FLAGS)", addr);
            return -1;
        }
    }

    optParam = SO_TLS_UNCLEAN_SHUTDOWN;
    WSAIoctl(s, SO_SSL_SET_FLAGS, (char *)&optParam, sizeof(optParam),
             NULL, 0, NULL, NULL, NULL);

    return s;
}

static int convert_secure_socket(conn_rec *c, apr_socket_t *csd)
{
    int rcode;
    struct tlsclientopts sWS2Opts;
    struct nwtlsopts sNWTLSOpts;
    struct sslserveropts opts;
    unsigned long ulFlags;
    SOCKET sock;
    unicode_t keyFileName[60];

    apr_os_sock_get(&sock, csd);

    /* zero out buffers */
    memset((char *)&sWS2Opts, 0, sizeof(struct tlsclientopts));
    memset((char *)&sNWTLSOpts, 0, sizeof(struct nwtlsopts));

    /* turn on ssl for the socket */
    ulFlags = (numcerts ? SO_TLS_ENABLE : SO_TLS_ENABLE | SO_TLS_BLIND_ACCEPT);
    rcode = WSAIoctl(sock, SO_TLS_SET_FLAGS, &ulFlags, sizeof(unsigned long),
                     NULL, 0, NULL, NULL, NULL);
    if (SOCKET_ERROR == rcode) {
        ap_log_error(APLOG_MARK, APLOG_ERR, 0, c->base_server,
                     "Error: %d with ioctlsocket(flag SO_TLS_ENABLE)",
                     WSAGetLastError());
        return rcode;
    }

    ulFlags = SO_TLS_UNCLEAN_SHUTDOWN;
    WSAIoctl(sock, SO_TLS_SET_FLAGS, &ulFlags, sizeof(unsigned long),
             NULL, 0, NULL, NULL, NULL);

    /* setup the socket for SSL */
    memset (&sWS2Opts, 0, sizeof(sWS2Opts));
    memset (&sNWTLSOpts, 0, sizeof(sNWTLSOpts));
    sWS2Opts.options = &sNWTLSOpts;

    if (numcerts) {
        sNWTLSOpts.walletProvider = WAL_PROV_DER;  /* the wallet provider defined in wdefs.h */
        sNWTLSOpts.TrustedRootList = certarray;    /* array of certs in UNICODE format */
        sNWTLSOpts.numElementsInTRList = numcerts; /* number of certs in TRList */
    }
    else {
        /* setup the socket for SSL */
    	unicpy(keyFileName, L"SSL CertificateIP");
        sWS2Opts.wallet = keyFileName;             /* no client certificate */
    	sWS2Opts.walletlen = unilen(keyFileName);

        sNWTLSOpts.walletProvider = WAL_PROV_KMO;  /* the wallet provider defined in wdefs.h */
    }

    /* make the IOCTL call */
    rcode = WSAIoctl(sock, SO_TLS_SET_CLIENT, &sWS2Opts,
                     sizeof(struct tlsclientopts), NULL, 0, NULL,
                     NULL, NULL);

    /* make sure that it was successfull */
    if(SOCKET_ERROR == rcode ){
    ap_log_error(APLOG_MARK, APLOG_ERR, 0, c->base_server,
                 "Error: %d with ioctl (SO_TLS_SET_CLIENT)",
                 WSAGetLastError());
    }
    return rcode;
}

static int SSLize_Socket(SOCKET socketHnd, char *key, request_rec *r)
{
    int rcode;
    struct tlsserveropts sWS2Opts;
    struct nwtlsopts    sNWTLSOpts;
    unicode_t SASKey[512];
    unsigned long ulFlag;

    memset((char *)&sWS2Opts, 0, sizeof(struct tlsserveropts));
    memset((char *)&sNWTLSOpts, 0, sizeof(struct nwtlsopts));


    ulFlag = SO_TLS_ENABLE;
    rcode = WSAIoctl(socketHnd, SO_TLS_SET_FLAGS, &ulFlag,
                     sizeof(unsigned long), NULL, 0, NULL, NULL, NULL);
    if(rcode) {
        ap_log_error(APLOG_MARK, APLOG_ERR, 0, r->server,
                     "Error: %d with WSAIoctl(SO_TLS_SET_FLAGS, SO_TLS_ENABLE)",
                     WSAGetLastError());
        goto ERR;
    }


    ulFlag = SO_TLS_SERVER;
    rcode = WSAIoctl(socketHnd, SO_TLS_SET_FLAGS, &ulFlag,
                     sizeof(unsigned long),NULL, 0, NULL, NULL, NULL);

    if(rcode) {
        ap_log_error(APLOG_MARK, APLOG_ERR, 0, r->server,
                     "Error: %d with WSAIoctl(SO_TLS_SET_FLAGS, SO_TLS_SERVER)",
                     WSAGetLastError());
        goto ERR;
    }

    loc2uni(UNI_LOCAL_DEFAULT, SASKey, key, 0, 0);

    /* setup the tlsserveropts struct */
    sWS2Opts.wallet = SASKey;
    sWS2Opts.walletlen = unilen(SASKey);
    sWS2Opts.sidtimeout = 0;
    sWS2Opts.sidentries = 0;
    sWS2Opts.siddir = NULL;
    sWS2Opts.options = &sNWTLSOpts;

    /* setup the nwtlsopts structure */

    sNWTLSOpts.walletProvider          = WAL_PROV_KMO;
    sNWTLSOpts.keysList                = NULL;
    sNWTLSOpts.numElementsInKeyList    = 0;
    sNWTLSOpts.reservedforfutureuse    = NULL;
    sNWTLSOpts.reservedforfutureCRL    = NULL;
    sNWTLSOpts.reservedforfutureCRLLen = 0;
    sNWTLSOpts.reserved1               = NULL;
    sNWTLSOpts.reserved2               = NULL;
    sNWTLSOpts.reserved3               = NULL;


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
                     "Error: %d with WSAIoctl(SO_TLS_SET_SERVER)",
                     WSAGetLastError());
        goto ERR;
    }

ERR:
    return rcode;
}

static const char *set_secure_listener(cmd_parms *cmd, void *dummy,
                                       const char *ips, const char* key,
                                       const char* mutual)
{
    NWSSLSrvConfigRec* sc = get_nwssl_cfg(cmd->server);
    const char *err = ap_check_cmd_context(cmd, GLOBAL_ONLY);
    char *ports, *addr;
    unsigned short port;
    seclisten_rec *new;


    if (err != NULL)
        return err;

    ports = strchr(ips, ':');

    if (ports != NULL) {
	    if (ports == ips)
	        return "Missing IP address";
	    else if (ports[1] == '\0')
	        return "Address must end in :<port-number>";

	    *(ports++) = '\0';
    }
    else {
	    ports = (char*)ips;
    }

    new = apr_pcalloc(cmd->pool, sizeof(seclisten_rec));
    new->local_addr.sin_family = AF_INET;

    if (ports == ips) {
	    new->local_addr.sin_addr.s_addr = htonl(INADDR_ANY);
        addr = apr_pstrdup(cmd->pool, "0.0.0.0");
    }
    else {
	    new->local_addr.sin_addr.s_addr = parse_addr(ips, NULL);
        addr = apr_pstrdup(cmd->pool, ips);
    }

    port = atoi(ports);

    if (!port)
        return "Port must be numeric";

    apr_table_add(sc->sltable, ports, addr);

    new->local_addr.sin_port = htons(port);
    new->fd = -1;
    new->used = 0;
    new->next = ap_seclisteners;
    strcpy(new->key, key);
    new->mutual = (mutual) ? 1 : 0;
    new->addr = addr;
    new->port = port;
    ap_seclisteners = new;
    return NULL;
}

static const char *set_secure_upgradeable_listener(cmd_parms *cmd,
                                                   void *dummy,
                                                   const char *ips,
                                                   const char *key)
{
    NWSSLSrvConfigRec* sc = get_nwssl_cfg(cmd->server);
    seclistenup_rec *listen_node;
    const char *err = ap_check_cmd_context(cmd, GLOBAL_ONLY);
    char *ports, *addr;
    unsigned short port;
    seclistenup_rec *new;

    if (err != NULL)
        return err;

    ports = strchr(ips, ':');

    if (ports != NULL) {
        if (ports == ips)
            return "Missing IP address";
        else if (ports[1] == '\0')
            return "Address must end in :<port-number>";

        *(ports++) = '\0';
    }
    else {
        ports = (char*)ips;
    }

    if (ports == ips) {
        addr = apr_pstrdup(cmd->pool, "0.0.0.0");
    }
    else {
        addr = apr_pstrdup(cmd->pool, ips);
    }

    port = atoi(ports);

    if (!port)
        return "Port must be numeric";

    apr_table_set(sc->slutable, ports, addr);

    new = apr_pcalloc(cmd->pool, sizeof(seclistenup_rec));
    new->next = ap_seclistenersup;
    strcpy(new->key, key);
    new->addr = addr;
    new->port = port;
    ap_seclistenersup = new;

