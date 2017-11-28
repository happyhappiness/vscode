static void
idnsTickleQueue(void)
{
    if (event_queued)
        return;

    if (NULL == lru_list.tail)
        return;

    eventAdd("idnsCheckQueue", idnsCheckQueue, NULL, 1.0, 1);

    event_queued = 1;
}