static void
idnsCheckMDNS(idns_query *q)
{
    if (!Config.onoff.dns_mdns || q->permit_mdns)
        return;

    size_t slen = strlen(q->name);
    if (slen > 6 && memcmp(q->name +(slen-6),".local", 6) == 0) {
        q->permit_mdns = true;
    }
}