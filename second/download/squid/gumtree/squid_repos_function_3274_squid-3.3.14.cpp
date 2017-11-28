Comm::ConnectionPointer
IdleConnList::pop()
{
    for (int i=size_-1; i>=0; --i) {

        if (!isAvailable(i))
            continue;

        // our connection timeout handler is scheduled to run already. unsafe for now.
        // TODO: cancel the pending timeout callback and allow re-use of the conn.
        if (fd_table[theList_[i]->fd].timeoutHandler == NULL)
            continue;

        // finally, a match. pop and return it.
        Comm::ConnectionPointer result = theList_[i];
        /* may delete this */
        removeAt(i);
        clearHandlers(result);
        return result;
    }

    return Comm::ConnectionPointer();
}