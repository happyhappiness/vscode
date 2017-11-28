static void
icapLookupDnsResults(const ipcache_addrs *ia, const DnsLookupDetails &, void *data)
{
    Adaptation::Icap::Xaction *xa = static_cast<Adaptation::Icap::Xaction *>(data);
    xa->dnsLookupDone(ia);
}