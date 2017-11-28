static void
clientHttpConnectionsOpen(void)
{
    AnyP::PortCfg *s = NULL;

    for (s = Config.Sockaddr.http; s; s = s->next) {
        if (MAXTCPLISTENPORTS == NHttpSockets) {
            debugs(1, DBG_IMPORTANT, "WARNING: You have too many 'http_port' lines.");
            debugs(1, DBG_IMPORTANT, "         The limit is " << MAXTCPLISTENPORTS << " HTTP ports.");
            continue;
        }

#if USE_SSL
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
#endif

        // Fill out a Comm::Connection which IPC will open as a listener for us
        //  then pass back when active so we can start a TcpAcceptor subscription.
        s->listenConn = new Comm::Connection;
        s->listenConn->local = s->s;
        s->listenConn->flags = COMM_NONBLOCKING | (s->spoof_client_ip ? COMM_TRANSPARENT : 0) | (s->intercepted ? COMM_INTERCEPTION : 0);

        // setup the subscriptions such that new connections accepted by listenConn are handled by HTTP
        typedef CommCbFunPtrCallT<CommAcceptCbPtrFun> AcceptCall;
        RefCount<AcceptCall> subCall = commCbCall(5, 5, "httpAccept", CommAcceptCbPtrFun(httpAccept, s));
        Subscription::Pointer sub = new CallSubscription<AcceptCall>(subCall);

        AsyncCall::Pointer listenCall = asyncCall(33,2, "clientListenerConnectionOpened",
                                        ListeningStartedDialer(&clientListenerConnectionOpened, s, Ipc::fdnHttpSocket, sub));
        Ipc::StartListening(SOCK_STREAM, IPPROTO_TCP, s->listenConn, Ipc::fdnHttpSocket, listenCall);

        HttpSockets[NHttpSockets] = -1; // set in clientListenerConnectionOpened
        ++NHttpSockets;
    }
}