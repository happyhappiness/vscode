int
ACLDestinationASNStrategy::match (ACLData<MatchType> * &data, ACLFilledChecklist *checklist)
{
    const ipcache_addrs *ia = ipcache_gethostbyname(checklist->request->GetHost(), IP_LOOKUP_IF_MISS);

    if (ia) {
        for (int k = 0; k < (int) ia->count; ++k) {
            if (data->match(ia->in_addrs[k]))
                return 1;
        }

        return 0;

    } else if (!checklist->request->flags.destinationIpLookedUp) {
        /* No entry in cache, lookup not attempted */
        /* XXX FIXME: allow accessing the acl name here */
        debugs(28, 3, "asnMatchAcl: Can't yet compare '" << "unknown" /*name*/ << "' ACL for '" << checklist->request->GetHost() << "'");
        checklist->changeState (DestinationIPLookup::Instance());
    } else {
        Ip::Address noaddr;
        noaddr.SetNoAddr();
        return data->match(noaddr);
    }

    return 0;
}