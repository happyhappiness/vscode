static void
hostHeaderIpVerifyWrapper(const ipcache_addrs* ia, const Dns::LookupDetails &dns, void *data)
{
    ClientRequestContext *c = static_cast<ClientRequestContext*>(data);
    c->hostHeaderIpVerify(ia, dns);
}