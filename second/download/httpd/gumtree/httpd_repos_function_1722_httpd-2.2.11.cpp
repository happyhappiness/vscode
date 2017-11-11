static int make_secure_socket(apr_pool_t *pconf, const struct sockaddr_in *server,
                              char* key, int mutual, server_rec *sconf)
{
    int s;
    int one = 1;
    char addr[MAX_ADDRESS];
    struct sslserveropts opts;
    unsigned int optParam;
    WSAPROTOCOL_INFO SecureProtoInfo;
    int no = 1;

    if (server->sin_addr.s_addr != htonl(INADDR_ANY))
        apr_snprintf(addr, sizeof(addr), "address %s port %d",
            inet_ntoa(server->sin_addr), ntohs(server->sin_port));
    else
        apr_snprintf(addr, sizeof(addr), "port %d", ntohs(server->sin_port));

    /* note that because we're about to slack we don't use psocket */
    memset(&SecureProtoInfo, 0, sizeof(WSAPROTOCOL_INFO));

    SecureProtoInfo.iAddressFamily = AF_INET;
    SecureProtoInfo.iSocketType = SOCK_STREAM;
    SecureProtoInfo.iProtocol = IPPROTO_TCP;
    SecureProtoInfo.iSecurityScheme = SECURITY_PROTOCOL_SSL;

    s = WSASocket(AF_INET, SOCK_STREAM, IPPROTO_TCP,
            (LPWSAPROTOCOL_INFO)&SecureProtoInfo, 0, 0);

    if (s == INVALID_SOCKET) {
        ap_log_error(APLOG_MARK, APLOG_CRIT, WSAGetLastError(), sconf,
                     "make_secure_socket: failed to get a socket for %s",
                     addr);
        return -1;
    }

    if (!mutual) {
        optParam = SO_SSL_ENABLE | SO_SSL_SERVER;

        if (WSAIoctl(s, SO_SSL_SET_FLAGS, (char *)&optParam,
            sizeof(optParam), NULL, 0, NULL, NULL, NULL)) {
            ap_log_error(APLOG_MARK, APLOG_CRIT, WSAGetLastError(), sconf,
                         "make_secure_socket: for %s, WSAIoctl: "
                         "(SO_SSL_SET_FLAGS)", addr);
            return -1;
        }
    }

    opts.cert = key;
    opts.certlen = strlen(key);
    opts.sidtimeout = 0;
    opts.sidentries = 0;
    opts.siddir = NULL;

    if (WSAIoctl(s, SO_SSL_SET_SERVER, (char *)&opts, sizeof(opts),
        NULL, 0, NULL, NULL, NULL) != 0) {
        ap_log_error(APLOG_MARK, APLOG_CRIT, WSAGetLastError(), sconf,
                     "make_secure_socket: for %s, WSAIoctl: "
                     "(SO_SSL_SET_SERVER)", addr);
        return -1;
    }

    if (mutual) {
        optParam = 0x07;  // SO_SSL_AUTH_CLIENT

        if(WSAIoctl(s, SO_SSL_SET_FLAGS, (char*)&optParam,
            sizeof(optParam), NULL, 0, NULL, NULL, NULL)) {
            ap_log_error(APLOG_MARK, APLOG_CRIT, WSAGetLastError(), sconf,
                         "make_secure_socket: for %s, WSAIoctl: "
                         "(SO_SSL_SET_FLAGS)", addr);
            return -1;
        }
    }

    optParam = SO_TLS_UNCLEAN_SHUTDOWN;
    WSAIoctl(s, SO_SSL_SET_FLAGS, (char *)&optParam, sizeof(optParam),
             NULL, 0, NULL, NULL, NULL);

    return s;
}