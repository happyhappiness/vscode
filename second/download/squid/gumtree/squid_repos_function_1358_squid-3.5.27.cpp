static void
peerAddFwdServer(FwdServer ** FSVR, CachePeer * p, hier_code code)
{
    debugs(44, 5, "peerAddFwdServer: adding " <<
           (p ? p->host : "DIRECT")  << " " <<
           hier_code_str[code]  );
    FwdServer *fs = new FwdServer(p, code);

    while (*FSVR)
        FSVR = &(*FSVR)->next;

    *FSVR = fs;
}