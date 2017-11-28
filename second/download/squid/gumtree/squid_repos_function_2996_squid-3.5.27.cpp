static void
clientdbGC(void *unused)
{
    static int bucket = 0;
    hash_link *link_next;

    link_next = hash_get_bucket(client_table, bucket++);

    while (link_next != NULL) {
        ClientInfo *c = (ClientInfo *)link_next;
        int age = squid_curtime - c->last_seen;
        link_next = link_next->next;

        if (c->n_established)
            continue;

        if (age < 24 * 3600 && c->Http.n_requests > 100)
            continue;

        if (age < 4 * 3600 && (c->Http.n_requests > 10 || c->Icp.n_requests > 10))
            continue;

        if (age < 5 * 60 && (c->Http.n_requests > 1 || c->Icp.n_requests > 1))
            continue;

        if (age < 60)
            continue;

        hash_remove_link(client_table, &c->hash);

        clientdbFreeItem(c);

        --statCounter.client_http.clients;

        ++cleanup_removed;
    }

    if (bucket < CLIENT_DB_HASH_SIZE)
        eventAdd("client_db garbage collector", clientdbGC, NULL, 0.15, 0);
    else {
        bucket = 0;
        cleanup_running = 0;
        max_clients = statCounter.client_http.clients * 3 / 2;

        if (!cleanup_scheduled) {
            cleanup_scheduled = 1;
            eventAdd("client_db garbage collector", clientdbScheduledGC, NULL, 6 * 3600, 0);
        }

        debugs(49, 2, "clientdbGC: Removed " << cleanup_removed << " entries");
    }
}