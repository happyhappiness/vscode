static void
clientHttpsConnectionsOpen(void)
{
    AnyP::PortCfg *s;

    for (s = Config.Sockaddr.https; s; s = s->next) {
        if (MAXTCPLISTENPORTS == NHttpSockets) {
            debugs(1, DBG_IMPORTANT, "Ignoring 'https_port' lines exceeding the limit.");
            debugs(1, DBG_IMPORTANT, "The limit is " << MAXTCPLISTENPORTS << " HTTPS ports.");
            continue;
        }

        if (!s->staticSslContext) {
            debugs(1, DBG_IMPORTANT, "Ignoring https_port " << s->s <<
                   " due to SSL initialization failure.");
            continue;
        }

        // TODO: merge with similar code in clientHttpConnectionsOpen()
        if (s->sslBump && !Config.accessList.ssl_bump) {
            debugs(33, DBG_IMPORTANT, "WARNING: No ssl_bump configured. Disabling ssl-bump on " << s->protocol << "_port " << s->s);
            s->sslBump = 0;
        }

        if (s->sslBump && !s->staticSslContext && !s->generateHostCertificates) {
            debugs(1, DBG_IMPORTANT, "Will not bump SSL at http_port " << s->s << " due to SSL initialization failure.");
            s->sslBump = 0;
        }

        if (s->sslBump) {
            // Create ssl_ctx cache for this port.
            Ssl::TheGlobalContextStorage.addLocalStorage(s->s, s->dynamicCertMemCacheSize == std::numeric_limits<size_t>::max() ? 4194304 : s->dynamicCertMemCacheSize);
        }

        // Fill out a Comm::Connection which IPC will open as a listener for us
        s->listenConn = new Comm::Connection;
        s->listenConn->local = s->s;
        s->listenConn->flags = COMM_NONBLOCKING | (s->spoof_client_ip ? COMM_TRANSPARENT : 0) |
                               (s->intercepted ? COMM_INTERCEPTION : 0);

        // setup the subscriptions such that new connections accepted by listenConn are handled by HTTPS
        typedef CommCbFunPtrCallT<CommAcceptCbPtrFun> AcceptCall;
        RefCount<AcceptCall> subCall = commCbCall(5, 5, "httpsAccept", CommAcceptCbPtrFun(httpsAccept, s));
        Subscription::Pointer sub = new CallSubscription<AcceptCall>(subCall);

        AsyncCall::Pointer listenCall = asyncCall(33, 2, "clientListenerConnectionOpened",
                                        ListeningStartedDialer(&clientListenerConnectionOpened,
                                                               s, Ipc::fdnHttpsSocket, sub));
        Ipc::StartListening(SOCK_STREAM, IPPROTO_TCP, s->listenConn, Ipc::fdnHttpsSocket, listenCall);
        HttpSockets[NHttpSockets] = -1;
        ++NHttpSockets;
    }
}