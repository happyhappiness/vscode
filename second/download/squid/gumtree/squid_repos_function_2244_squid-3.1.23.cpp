void
idnsALookup(const char *name, IDNSCB * callback, void *data)
{
    unsigned int i;
    int nd = 0;
    idns_query *q;

    if (idnsCachedLookup(name, callback, data))
        return;

    q = cbdataAlloc(idns_query);

    q->id = idnsQueryID();

    for (i = 0; i < strlen(name); i++)
        if (name[i] == '.')
            nd++;

    if (Config.onoff.res_defnames && npc > 0 && name[strlen(name)-1] != '.') {
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

    if (Ip::EnableIpv6) {
        q->sz = rfc3596BuildAAAAQuery(q->name, q->buf, sizeof(q->buf), q->id, &q->query);
        q->need_A = true;
    } else {
        q->sz = rfc3596BuildAQuery(q->name, q->buf, sizeof(q->buf), q->id, &q->query);
        q->need_A = false;
    }

    if (q->sz < 0) {
        /* problem with query data -- query not sent */
        callback(data, NULL, 0, "Internal error");
        cbdataFree(q);
        return;
    }

    debugs(78, 3, "idnsALookup: buf is " << q->sz << " bytes for " << q->name <<
           ", id = 0x" << std::hex << q->id);

    q->callback = callback;
    q->callback_data = cbdataReference(data);

    q->start_t = current_time;

    idnsCacheQuery(q);
    idnsSendQuery(q);
}