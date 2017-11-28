static void
idnsTickleQueue(void)
{
    if (event_queued)
        return;

    if (NULL == lru_list.tail)
        return;

    const double when = min(Config.Timeout.idns_query, Config.Timeout.idns_retransmit)/1000.0;

    eventAdd("idnsCheckQueue", idnsCheckQueue, NULL, when, 1);

    event_queued = 1;
}