void
idnsALookup(const char *name, IDNSCB * callback, void *data)
{
    size_t nameLength = strlen(name);

    // Prevent buffer overflow on q->name
    if (nameLength > NS_MAXDNAME) {
        debugs(23, DBG_IMPORTANT, "SECURITY ALERT: DNS name too long to perform lookup: '" << name << "'. see access.log for details.");
        callback(data, NULL, 0, "Internal error");
        return;
    }

    if (idnsCachedLookup(name, callback, data))
        return;

    idns_query *q = cbdataAlloc(idns_query);
    // idns_query is POD so no constructors are called after allocation
    q->xact_id.change();
    q->query_id = idnsQueryID();

    int nd = 0;
    for (unsigned int i = 0; i < nameLength; ++i)
        if (name[i] == '.')
            ++nd;

    if (Config.onoff.res_defnames && npc > 0 && name[nameLength-1] != '.') {
        q->do_searchpath = 1;
    } else {
        q->do_searchpath = 0;
    }

    strcpy(q->orig, name);
    strcpy(q->name, q->orig);

    if (q->do_searchpath && nd < ndots) {
        q->domain = 0;
        strcat(q->name, ".");
        strcat(q->name, searchpath[q->domain].domain);
        debugs(78, 3, "idnsALookup: searchpath used for " << q->name);
    }

    // see EDNS notes at top of file why this sends 0
    q->sz = rfc3596BuildAQuery(q->name, q->buf, sizeof(q->buf), q->query_id, &q->query, 0);

    if (q->sz < 0) {
        /* problem with query data -- query not sent */
        callback(data, NULL, 0, "Internal error");
        cbdataFree(q);
        return;
    }

    debugs(78, 3, "idnsALookup: buf is " << q->sz << " bytes for " << q->name <<
           ", id = 0x" << std::hex << q->query_id);

    idnsStartQuery(q, callback, data);

    if (Ip::EnableIpv6)
        idnsSendSlaveAAAAQuery(q);

}