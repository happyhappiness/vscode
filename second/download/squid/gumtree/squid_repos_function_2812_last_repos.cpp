Comm::ConnectionPointer
IdleConnList::findUseable(const Comm::ConnectionPointer &aKey)
{
    assert(size_);

    // small optimization: do the constant bool tests only once.
    const bool keyCheckAddr = !aKey->local.isAnyAddr();
    const bool keyCheckPort = aKey->local.port() > 0;

    for (int i=size_-1; i>=0; --i) {

        if (!isAvailable(i))
            continue;

        // local end port is required, but dont match.
        if (keyCheckPort && aKey->local.port() != theList_[i]->local.port())
            continue;

        // local address is required, but does not match.
        if (keyCheckAddr && aKey->local.matchIPAddr(theList_[i]->local) != 0)
            continue;

        // our connection timeout handler is scheduled to run already. unsafe for now.
        // TODO: cancel the pending timeout callback and allow re-use of the conn.
        if (fd_table[theList_[i]->fd].timeoutHandler == NULL)
            continue;

        // finally, a match. pop and return it.
        Comm::ConnectionPointer result = theList_[i];
        clearHandlers(result);
        /* may delete this */
        removeAt(i);
        return result;
    }

    return Comm::ConnectionPointer();
}