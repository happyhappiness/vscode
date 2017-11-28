static void
idnsStats(StoreEntry * sentry)
{
    dlink_node *n;
    idns_query *q;
    int i;
    int j;
    char buf[MAX_IPSTRLEN];
    storeAppendPrintf(sentry, "Internal DNS Statistics:\n");
    storeAppendPrintf(sentry, "\nThe Queue:\n");
    storeAppendPrintf(sentry, "                       DELAY SINCE\n");
    storeAppendPrintf(sentry, "  ID   SIZE SENDS FIRST SEND LAST SEND\n");
    storeAppendPrintf(sentry, "------ ---- ----- ---------- ---------\n");

    for (n = lru_list.head; n; n = n->next) {
        q = (idns_query *)n->data;
        storeAppendPrintf(sentry, "%#06x %4d %5d %10.3f %9.3f\n",
                          (int) q->id, (int) q->sz, q->nsends,
                          tvSubDsec(q->start_t, current_time),
                          tvSubDsec(q->sent_t, current_time));
    }

    storeAppendPrintf(sentry, "\nNameservers:\n");
    storeAppendPrintf(sentry, "IP ADDRESS                                     # QUERIES # REPLIES\n");
    storeAppendPrintf(sentry, "---------------------------------------------- --------- ---------\n");

    for (i = 0; i < nns; i++) {
        storeAppendPrintf(sentry, "%-45s %9d %9d\n",  /* Let's take the maximum: (15 IPv4/45 IPv6) */
                          nameservers[i].S.NtoA(buf,MAX_IPSTRLEN),
                          nameservers[i].nqueries,
                          nameservers[i].nreplies);
    }

    storeAppendPrintf(sentry, "\nRcode Matrix:\n");
    storeAppendPrintf(sentry, "RCODE");

    for (i = 0; i < MAX_ATTEMPT; i++)
        storeAppendPrintf(sentry, " ATTEMPT%d", i + 1);

    storeAppendPrintf(sentry, "\n");

    for (j = 0; j < MAX_RCODE; j++) {
        storeAppendPrintf(sentry, "%5d", j);

        for (i = 0; i < MAX_ATTEMPT; i++)
            storeAppendPrintf(sentry, " %8d", RcodeMatrix[j][i]);

        storeAppendPrintf(sentry, "\n");
    }

    if (npc) {
        storeAppendPrintf(sentry, "\nSearch list:\n");

        for (i=0; i < npc; i++)
            storeAppendPrintf(sentry, "%s\n", searchpath[i].domain);

        storeAppendPrintf(sentry, "\n");
    }
}