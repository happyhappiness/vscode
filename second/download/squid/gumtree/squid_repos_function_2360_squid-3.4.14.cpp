static bool
idnsParseNameservers(void)
{
    bool result = false;
    for (wordlist *w = Config.dns_nameservers; w; w = w->next) {
        debugs(78, DBG_IMPORTANT, "Adding nameserver " << w->key << " from squid.conf");
        idnsAddNameserver(w->key);
        result = true;
    }
    return result;
}