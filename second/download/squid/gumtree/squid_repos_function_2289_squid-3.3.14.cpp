static void
idnsParseNameservers(void)
{
    wordlist *w;

    for (w = Config.dns_nameservers; w; w = w->next) {
        debugs(78, DBG_IMPORTANT, "Adding nameserver " << w->key << " from squid.conf");
        idnsAddNameserver(w->key);
    }
}