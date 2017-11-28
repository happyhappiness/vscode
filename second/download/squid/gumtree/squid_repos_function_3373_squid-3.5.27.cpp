void
PconnPool::push(const Comm::ConnectionPointer &conn, const char *domain)
{
    if (fdUsageHigh()) {
        debugs(48, 3, HERE << "Not many unused FDs");
        conn->close();
        return;
    } else if (shutting_down) {
        conn->close();
        debugs(48, 3, HERE << "Squid is shutting down. Refusing to do anything");
        return;
    }
    // TODO: also close used pconns if we exceed peer max-conn limit

    const char *aKey = key(conn, domain);
    IdleConnList *list = (IdleConnList *) hash_lookup(table, aKey);

    if (list == NULL) {
        list = new IdleConnList(aKey, this);
        debugs(48, 3, HERE << "new IdleConnList for {" << hashKeyStr(&list->hash) << "}" );
        hash_join(table, &list->hash);
    } else {
        debugs(48, 3, HERE << "found IdleConnList for {" << hashKeyStr(&list->hash) << "}" );
    }

    list->push(conn);
    assert(!comm_has_incomplete_write(conn->fd));

    LOCAL_ARRAY(char, desc, FD_DESC_SZ);
    snprintf(desc, FD_DESC_SZ, "Idle server: %s", aKey);
    fd_note(conn->fd, desc);
    debugs(48, 3, HERE << "pushed " << conn << " for " << aKey);

    // successful push notifications resume multi-connection opening sequence
    notifyManager("push");
}