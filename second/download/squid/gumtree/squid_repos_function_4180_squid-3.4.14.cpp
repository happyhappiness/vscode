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