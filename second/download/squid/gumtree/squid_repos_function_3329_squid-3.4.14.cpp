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