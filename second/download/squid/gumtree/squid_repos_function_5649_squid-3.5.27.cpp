bool
Comm::TcpAcceptor::doneAll() const
{
    // stop when FD is closed
    if (!IsConnOpen(conn)) {
        return AsyncJob::doneAll();
    }

    // stop when handlers are gone
    if (theCallSub == NULL) {
        return AsyncJob::doneAll();
    }

    // open FD with handlers...keep accepting.
    return false;
}