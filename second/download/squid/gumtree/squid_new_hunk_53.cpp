        if (serv) {
            writeableCfg().port = htons(serv->s_port);
        } else {
            writeableCfg().port = 1344;
        }
    }

    theSessionFailures.configure(TheConfig.oldest_service_failure > 0 ?
                                 TheConfig.oldest_service_failure : -1);
}

void Adaptation::Icap::ServiceRep::noteFailure()
{
    const int failures = theSessionFailures.count(1);
    debugs(93,4, HERE << " failure " << failures << " out of " <<
           TheConfig.service_failure_limit << " allowed in " <<
           TheConfig.oldest_service_failure << "sec " << status());

    if (isSuspended)
        return;

    if (TheConfig.service_failure_limit >= 0 &&
            failures > TheConfig.service_failure_limit)
        suspend("too many failures");

    // TODO: Should bypass setting affect how much Squid tries to talk to
    // the ICAP service that is currently unusable and is likely to remain
    // so for some time? The current code says "no". Perhaps the answer
    // should be configurable.
}

// returns a persistent or brand new connection; negative int on failures
Comm::ConnectionPointer
Adaptation::Icap::ServiceRep::getConnection(bool retriableXact, bool &reused)
{
    Comm::ConnectionPointer connection;

    /* 2011-06-17: rousskov:
     *  There are two things that happen at the same time in pop(). Both are important.
     *    1) Ensure that we can use a pconn for this transaction.
     *    2) Ensure that the number of idle pconns does not grow without bounds.
     *
     * Both happen in the beginning of the transaction. Both are dictated by real-world problems.
     * retriable means you can repeat the request if you suspect the first try failed due to a pconn race.
     * HTTP and ICAP rules prohibit the use of pconns for non-retriable requests.
     *
     * If there are zero idle connections, (2) is irrelevant. (2) is only relevant when there are many
     * idle connections and we should not open more connections without closing some idle ones,
     * or instead of just opening a new connection and leaving idle connections as is.
     * In other words, (2) tells us to close one FD for each new one we open due to retriable.
     */
    if (retriableXact)
        connection = theIdleConns->pop();
    else
        theIdleConns->closeN(1);

    reused = Comm::IsConnOpen(connection);
    ++theBusyConns;
    debugs(93,3, HERE << "got connection: " << connection);
    return connection;
}

// pools connection if it is reusable or closes it
void Adaptation::Icap::ServiceRep::putConnection(const Comm::ConnectionPointer &conn, bool isReusable, bool sendReset, const char *comment)
{
    Must(Comm::IsConnOpen(conn));
    // do not pool an idle connection if we owe connections
    if (isReusable && excessConnections() == 0) {
        debugs(93, 3, HERE << "pushing pconn" << comment);
        commUnsetConnTimeout(conn);
        theIdleConns->push(conn);
    } else {
        debugs(93, 3, HERE << (sendReset ? "RST" : "FIN") << "-closing " <<
               comment);
        // comm_close called from Connection::close will clear timeout
        // TODO: add "bool sendReset = false" to Connection::close()?
        if (sendReset)
            comm_reset_close(conn);
        else
            conn->close();
    }

    Must(theBusyConns > 0);
    --theBusyConns;
    // a connection slot released. Check if there are waiters....
    busyCheckpoint();
}

// a wrapper to avoid exposing theIdleConns
void Adaptation::Icap::ServiceRep::noteConnectionUse(const Comm::ConnectionPointer &conn)
{
    Must(Comm::IsConnOpen(conn));
    fd_table[conn->fd].noteUse(NULL); // pconn re-use but not via PconnPool API
}

void Adaptation::Icap::ServiceRep::noteConnectionFailed(const char *comment)
{
    debugs(93, 3, HERE << "Connection failed: " << comment);
    --theBusyConns;
}

void Adaptation::Icap::ServiceRep::setMaxConnections()
{
    if (cfg().maxConn >= 0)
        theMaxConnections = cfg().maxConn;
    else if (theOptions && theOptions->max_connections >= 0)
        theMaxConnections = theOptions->max_connections;
    else {
        theMaxConnections = -1;
        return;
    }

    if (::Config.workers > 1 )
        theMaxConnections /= ::Config.workers;
}

int Adaptation::Icap::ServiceRep::availableConnections() const
{
    if (theMaxConnections < 0)
        return -1;

    // we are available if we can open or reuse connections
    // in other words, if we will not create debt
    int available = max(0, theMaxConnections - theBusyConns);

    if (!available && !connOverloadReported) {
        debugs(93, DBG_IMPORTANT, "WARNING: ICAP Max-Connections limit " <<
               "exceeded for service " << cfg().uri << ". Open connections now: " <<
               theBusyConns + theIdleConns->count() << ", including " <<
               theIdleConns->count() << " idle persistent connections.");
        connOverloadReported = true;
    }

    if (cfg().onOverload == srvForce)
        return -1;

    return available;
}

// The number of connections which excess the Max-Connections limit
int Adaptation::Icap::ServiceRep::excessConnections() const
{
    if (theMaxConnections < 0)
        return 0;

    // Waiters affect the number of needed connections but a needed
    // connection may still be excessive from Max-Connections p.o.v.
    // so we should not account for waiting transaction needs here.
    const int debt =  theBusyConns + theIdleConns->count() - theMaxConnections;
    if (debt > 0)
        return debt;
    else
        return 0;
}

void Adaptation::Icap::ServiceRep::noteGoneWaiter()
{
    --theAllWaiters;

    // in case the notified transaction did not take the connection slot
    busyCheckpoint();
}

// called when a connection slot may become available
void Adaptation::Icap::ServiceRep::busyCheckpoint()
{
    if (theNotificationWaiters.empty()) // nobody is waiting for a slot
        return;

    int freed = 0;
    int available = availableConnections();

    if (available < 0) {
        // It is possible to have waiters when no limit on connections exist in
        // case of reconfigure or because new Options received.
        // In this case, notify all waiting transactions.
        freed  = theNotificationWaiters.size();
    } else {
        // avoid notifying more waiters than there will be available slots
        const int notifiedWaiters = theAllWaiters - theNotificationWaiters.size();
        freed = available - notifiedWaiters;
    }

    debugs(93,7, HERE << "Available connections: " << available <<
           " freed slots: " << freed <<
           " waiting in queue: " << theNotificationWaiters.size());

    while (freed > 0 && !theNotificationWaiters.empty()) {
        Client i = theNotificationWaiters.front();
        theNotificationWaiters.pop_front();
        ScheduleCallHere(i.callback);
        i.callback = NULL;
        --freed;
    }
}

void Adaptation::Icap::ServiceRep::suspend(const char *reason)
{
    if (isSuspended) {
        debugs(93,4, HERE << "keeping suspended, also for " << reason);
    } else {
        isSuspended = reason;
