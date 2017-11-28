int

clientdbCutoffDenied(const Ip::Address &addr)
{
    char key[MAX_IPSTRLEN];
    int NR;
    int ND;
    double p;
    ClientInfo *c;

    if (!Config.onoff.client_db)
        return 0;

    addr.NtoA(key,MAX_IPSTRLEN);

    c = (ClientInfo *) hash_lookup(client_table, key);

    if (c == NULL)
        return 0;

    /*
     * If we are in a cutoff window, we don't send a reply
     */
    if (squid_curtime - c->cutoff.time < CUTOFF_SECONDS)
        return 1;

    /*
     * Calculate the percent of DENIED replies since the last
     * cutoff time.
     */
    NR = c->Icp.n_requests - c->cutoff.n_req;

    if (NR < 150)
        NR = 150;

    ND = c->Icp.result_hist[LOG_UDP_DENIED] - c->cutoff.n_denied;

    p = 100.0 * ND / NR;

    if (p < 95.0)
        return 0;

    debugs(1, DBG_CRITICAL, "WARNING: Probable misconfigured neighbor at " << key);

    debugs(1, DBG_CRITICAL, "WARNING: " << ND << " of the last " << NR <<
           " ICP replies are DENIED");

    debugs(1, DBG_CRITICAL, "WARNING: No replies will be sent for the next " <<
           CUTOFF_SECONDS << " seconds");

    c->cutoff.time = squid_curtime;

    c->cutoff.n_req = c->Icp.n_requests;

    c->cutoff.n_denied = c->Icp.result_hist[LOG_UDP_DENIED];

    return 1;
}