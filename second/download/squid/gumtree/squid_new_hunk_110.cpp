    sslHostName = host;

    //HTTPMSGLOCK(currentobject->http->request);
    assert(areAllContextsForThisConnection());
    freeAllContexts();
    //currentobject->connIsFinished();

    // We are going to read new request
    flags.readMore = true;
    debugs(33, 5, HERE << "converting " << clientConnection << " to SSL");

    return getSslContextStart();
}

#endif /* USE_SSL */

/// check FD after clientHttp[s]ConnectionOpened, adjust HttpSockets as needed
static bool
OpenedHttpSocket(const Comm::ConnectionPointer &c, const Ipc::FdNoteId portType)
{
    if (!Comm::IsConnOpen(c)) {
        Must(NHttpSockets > 0); // we tried to open some
        --NHttpSockets; // there will be fewer sockets than planned
        Must(HttpSockets[NHttpSockets] < 0); // no extra fds received

        if (!NHttpSockets) // we could not open any listen sockets at all
            fatalf("Unable to open %s",FdNote(portType));

        return false;
    }
    return true;
}

/// find any unused HttpSockets[] slot and store fd there or return false
static bool
AddOpenedHttpSocket(const Comm::ConnectionPointer &conn)
{
    bool found = false;
    for (int i = 0; i < NHttpSockets && !found; ++i) {
        if ((found = HttpSockets[i] < 0))
            HttpSockets[i] = conn->fd;
    }
    return found;
}

static void
clientHttpConnectionsOpen(void)
{
    AnyP::PortCfg *s = NULL;

    for (s = Config.Sockaddr.http; s; s = s->next) {
        if (MAXTCPLISTENPORTS == NHttpSockets) {
            debugs(1, 1, "WARNING: You have too many 'http_port' lines.");
            debugs(1, 1, "         The limit is " << MAXTCPLISTENPORTS << " HTTP ports.");
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

#if USE_SSL
static void
clientHttpsConnectionsOpen(void)
{
    AnyP::PortCfg *s;

    for (s = Config.Sockaddr.https; s; s = s->next) {
        if (MAXTCPLISTENPORTS == NHttpSockets) {
            debugs(1, 1, "Ignoring 'https_port' lines exceeding the limit.");
            debugs(1, 1, "The limit is " << MAXTCPLISTENPORTS << " HTTPS ports.");
            continue;
        }

        if (!s->staticSslContext) {
            debugs(1, 1, "Ignoring https_port " << s->s <<
                   " due to SSL initialization failure.");
            continue;
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
#endif

/// process clientHttpConnectionsOpen result
static void
clientListenerConnectionOpened(AnyP::PortCfg *s, const Ipc::FdNoteId portTypeNote, const Subscription::Pointer &sub)
{
    if (!OpenedHttpSocket(s->listenConn, portTypeNote))
        return;

    Must(s);
    Must(Comm::IsConnOpen(s->listenConn));

    // TCP: setup a job to handle accept() with subscribed handler
    AsyncJob::Start(new Comm::TcpAcceptor(s->listenConn, FdNote(portTypeNote), sub));

    debugs(1, 1, "Accepting " <<
           (s->intercepted ? "NAT intercepted " : "") <<
           (s->spoof_client_ip ? "TPROXY spoofing " : "") <<
           (s->sslBump ? "SSL bumped " : "") <<
           (s->accel ? "reverse-proxy " : "")
           << FdNote(portTypeNote) << " connections at "
           << s->listenConn);

    Must(AddOpenedHttpSocket(s->listenConn)); // otherwise, we have received a fd we did not ask for
}

void
clientOpenListenSockets(void)
{
    clientHttpConnectionsOpen();
#if USE_SSL
