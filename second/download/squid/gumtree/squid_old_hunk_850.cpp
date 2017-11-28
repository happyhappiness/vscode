    assert(!comm_has_incomplete_write(conn->fd));

    LOCAL_ARRAY(char, desc, FD_DESC_SZ);
    snprintf(desc, FD_DESC_SZ, "Idle server: %s", aKey);
    fd_note(conn->fd, desc);
    debugs(48, 3, HERE << "pushed " << conn << " for " << aKey);
}

Comm::ConnectionPointer
PconnPool::pop(const Comm::ConnectionPointer &destLink, const char *domain, bool isRetriable)
{
    const char * aKey = key(destLink, domain);

    IdleConnList *list = (IdleConnList *)hash_lookup(table, aKey);
    if (list == NULL) {
        debugs(48, 3, HERE << "lookup for key {" << aKey << "} failed.");
        return Comm::ConnectionPointer();
    } else {
        debugs(48, 3, HERE << "found " << hashKeyStr(&list->hash) << (isRetriable?"(to use)":"(to kill)") );
    }

    /* may delete list */
    Comm::ConnectionPointer temp = list->findUseable(destLink);
    if (!isRetriable && Comm::IsConnOpen(temp))
        temp->close();

    return temp;
}

void
PconnPool::closeN(int n, const Comm::ConnectionPointer &destLink, const char *domain)
{
    // TODO: optimize: we can probably do hash_lookup just once
    for (int i = 0; i < n; ++i)
        pop(destLink, domain, false); // may fail!
}

void
PconnPool::unlinkList(IdleConnList *list)
{
    theCount -= list->count();
