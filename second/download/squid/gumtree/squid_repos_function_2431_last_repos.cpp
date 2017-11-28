void
clientdbUpdate(const Ip::Address &addr, const LogTags &ltype, AnyP::ProtocolType p, size_t size)
{
    char key[MAX_IPSTRLEN];
    ClientInfo *c;

    if (!Config.onoff.client_db)
        return;

    addr.toStr(key,MAX_IPSTRLEN);

    c = (ClientInfo *) hash_lookup(client_table, key);

    if (c == NULL)
        c = clientdbAdd(addr);

    if (c == NULL)
        debug_trap("clientdbUpdate: Failed to add entry");

    if (p == AnyP::PROTO_HTTP) {
        ++ c->Http.n_requests;
        ++ c->Http.result_hist[ltype.oldType];
        c->Http.kbytes_out += size;

        if (ltype.isTcpHit())
            c->Http.hit_kbytes_out += size;
    } else if (p == AnyP::PROTO_ICP) {
        ++ c->Icp.n_requests;
        ++ c->Icp.result_hist[ltype.oldType];
        c->Icp.kbytes_out += size;

        if (LOG_UDP_HIT == ltype.oldType)
            c->Icp.hit_kbytes_out += size;
    }

    c->last_seen = squid_curtime;
}