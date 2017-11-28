static void
htcpClrStoreEntry(StoreEntry * e)
{
    debugs(31, 4, "htcpClrStoreEntry: Clearing store for entry: " << e->url()  );
    e->releaseRequest();
}