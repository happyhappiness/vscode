static void
ipcacheHandleReply(void *data, const rfc1035_rr * answers, int na, const char *error_message)
{
    ipcache_entry *i;
    static_cast<generic_cbdata *>(data)->unwrap(&i);
    ++IpcacheStats.replies;
    const int age = i->age();
    statCounter.dns.svcTime.count(age);

    ipcacheParse(i, answers, na, error_message);
    ipcacheAddEntry(i);
    ipcacheCallback(i, age);
}