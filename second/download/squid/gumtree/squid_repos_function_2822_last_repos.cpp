Comm::ConnectionPointer
PconnPool::pop(const Comm::ConnectionPointer &dest, const char *domain, bool keepOpen)
{

    const char * aKey = key(dest, domain);

    IdleConnList *list = (IdleConnList *)hash_lookup(table, aKey);
    if (list == NULL) {
        debugs(48, 3, HERE << "lookup for key {" << aKey << "} failed.");
        // failure notifications resume standby conn creation after fdUsageHigh
        notifyManager("pop failure");
        return Comm::ConnectionPointer();
    } else {
        debugs(48, 3, "found " << hashKeyStr(list) <<
               (keepOpen ? " to use" : " to kill"));
    }

    /* may delete list */
    Comm::ConnectionPointer popped = list->findUseable(dest);
    if (!keepOpen && Comm::IsConnOpen(popped))
        popped->close();

    // successful pop notifications replenish standby connections pool
    notifyManager("pop");
    return popped;
}