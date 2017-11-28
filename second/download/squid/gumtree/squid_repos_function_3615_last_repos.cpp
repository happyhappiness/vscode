static void
icapLookupDnsResults(const ipcache_addrs *ia, const Dns::LookupDetails &, void *data)
{
    Adaptation::Icap::Xaction *xa = static_cast<Adaptation::Icap::Xaction *>(data);
    xa->dnsLookupDone(ia);
}