bool
IdleConnList::isAvailable(int i) const
{
    const Comm::ConnectionPointer &conn = theList_[i];

    // connection already closed. useless.
    if (!Comm::IsConnOpen(conn))
        return false;

    // our connection early-read/close handler is scheduled to run already. unsafe
    if (!COMMIO_FD_READCB(conn->fd)->active())
        return false;

    return true;
}