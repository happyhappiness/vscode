int
PconnPool::pop(const char *host, unsigned short port, const char *domain, IpAddress &client_address, bool isRetriable)
{
    const char * aKey = key(host, port, domain, client_address);

    IdleConnList *list = (IdleConnList *)hash_lookup(table, aKey);
    if (list == NULL) {
        debugs(48, 3, "PconnPool::pop: lookup for key {" << aKey << "} failed.");
        return -1;
    } else {
        debugs(48, 3, "PconnPool::pop: found " << hashKeyStr(&list->hash) << (isRetriable?"(to use)":"(to kill)") );
    }

    int fd = list->findUseableFD(); // search from the end. skip pending reads.

    if (fd >= 0) {
        list->clearHandlers(fd);
        list->removeFD(fd);	/* might delete list */

        if (!isRetriable) {
            comm_close(fd);
            return -1;
        }
    }

    return fd;
}