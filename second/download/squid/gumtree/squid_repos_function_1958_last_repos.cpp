static void
idnsSendSlaveAAAAQuery(idns_query *master)
{
    idns_query *q = new idns_query;
    memcpy(q->name, master->name, sizeof(q->name));
    memcpy(q->orig, master->orig, sizeof(q->orig));
    q->master = master;
    q->query_id = idnsQueryID();
    q->sz = rfc3596BuildAAAAQuery(q->name, q->buf, sizeof(q->buf), q->query_id, &q->query, Config.dns.packet_max);

    debugs(78, 3, HERE << "buf is " << q->sz << " bytes for " << q->name <<
           ", id = 0x" << std::hex << q->query_id);
    if (!q->sz) {
        delete q;
        return;
    }

    q->start_t = master->start_t;
    q->slave = master->slave;

    idnsCheckMDNS(q);
    master->slave = q;
    idnsSendQuery(q);
}