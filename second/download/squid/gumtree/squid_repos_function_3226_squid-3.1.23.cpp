void
PconnPool::push(int fd, const char *host, unsigned short port, const char *domain, IpAddress &client_address)
{
    IdleConnList *list;
    const char *aKey;
    LOCAL_ARRAY(char, desc, FD_DESC_SZ);

    if (fdUsageHigh()) {
        debugs(48, 3, "PconnPool::push: Not many unused FDs");
        comm_close(fd);
        return;
    } else if (shutting_down) {
        comm_close(fd);
        debugs(48, 3, "PconnPool::push: Squid is shutting down. Refusing to do anything");
        return;
    }

    aKey = key(host, port, domain, client_address);

    list = (IdleConnList *) hash_lookup(table, aKey);

    if (list == NULL) {
        list = new IdleConnList(aKey, this);
        debugs(48, 3, "PconnPool::push: new IdleConnList for {" << hashKeyStr(&list->hash) << "}" );
        hash_join(table, &list->hash);
    } else {
        debugs(48, 3, "PconnPool::push: found IdleConnList for {" << hashKeyStr(&list->hash) << "}" );
    }

    list->push(fd);

    assert(!comm_has_incomplete_write(fd));
    snprintf(desc, FD_DESC_SZ, "%s idle connection", host);
    fd_note(fd, desc);
    debugs(48, 3, "PconnPool::push: pushed FD " << fd << " for " << aKey);
}