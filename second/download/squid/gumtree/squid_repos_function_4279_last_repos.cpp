int
ACLDestinationASNStrategy::match (ACLData<MatchType> * &data, ACLFilledChecklist *checklist)
{
    const ipcache_addrs *ia = ipcache_gethostbyname(checklist->request->url.host(), IP_LOOKUP_IF_MISS);

    if (ia) {
        for (int k = 0; k < (int) ia->count; ++k) {
            if (data->match(ia->in_addrs[k]))
                return 1;
        }

        return 0;

    } else if (!checklist->request->flags.destinationIpLookedUp) {
        /* No entry in cache, lookup not attempted */
        debugs(28, 3, "can't yet compare '" << AclMatchedName << "' ACL for " << checklist->request->url.host());
        if (checklist->goAsync(DestinationIPLookup::Instance()))
            return -1;
        // else fall through to noaddr match, hiding the lookup failure (XXX)
    }
    Ip::Address noaddr;
    noaddr.setNoAddr();
    return data->match(noaddr);
}