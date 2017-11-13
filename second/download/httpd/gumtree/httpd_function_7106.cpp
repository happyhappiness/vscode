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
        if (SOCKET_ERROR == rcode)
        {
        ap_log_error(APLOG_MARK, APLOG_ERR, 0, c->base_server, APLOGNO(02124)
                     "Error: %d with ioctlsocket(flag SO_TLS_ENABLE)", WSAGetLastError());
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
        sNWTLSOpts.walletProvider = WAL_PROV_DER;   /* the wallet provider defined in wdefs.h */
        sNWTLSOpts.TrustedRootList = certarray;     /* array of certs in UNICODE format       */
        sNWTLSOpts.numElementsInTRList = numcerts;  /* number of certs in TRList              */
    }
    else {
        /* setup the socket for SSL */
        unicpy(keyFileName, L"SSL CertificateIP");
        sWS2Opts.wallet = keyFileName;              /* no client certificate */
        sWS2Opts.walletlen = unilen(keyFileName);

        sNWTLSOpts.walletProvider = WAL_PROV_KMO;   /* the wallet provider defined in wdefs.h */
    }

    /* make the IOCTL call */
    rcode = WSAIoctl(sock, SO_TLS_SET_CLIENT, &sWS2Opts,
                     sizeof(struct tlsclientopts), NULL, 0, NULL,
                     NULL, NULL);

    /* make sure that it was successful */
        if(SOCKET_ERROR == rcode ){
        ap_log_error(APLOG_MARK, APLOG_ERR, 0, c->base_server, APLOGNO(02125)
                     "Error: %d with ioctl (SO_TLS_SET_CLIENT)", WSAGetLastError());
        }
        return rcode;
}