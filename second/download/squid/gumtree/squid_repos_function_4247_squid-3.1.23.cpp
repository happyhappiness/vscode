int
ACLDestinationDomainStrategy::match (ACLData<MatchType> * &data, ACLFilledChecklist *checklist)
{
    assert(checklist != NULL && checklist->request != NULL);

    if (data->match(checklist->request->GetHost())) {
        return 1;
    }

    /* numeric IPA? no, trust the above result. */
    if (checklist->request->GetHostIsNumeric() == 0) {
        return 0;
    }

    /* do we already have the rDNS? match on it if we do. */
    if (checklist->dst_rdns) {
        debugs(28, 3, "aclMatchAcl: '" << AclMatchedName << "' match with stored rDNS '" << checklist->dst_rdns << "' for '" << checklist->request->GetHost() << "'");
        return data->match(checklist->dst_rdns);
    }

    /* raw IP without rDNS? look it up and wait for the result */
    const ipcache_addrs *ia = ipcacheCheckNumeric(checklist->request->GetHost());
    if (!ia) {
        /* not a valid IPA */
        checklist->dst_rdns = xstrdup("invalid");
        return 0;
    }

    checklist->dst_addr = ia->in_addrs[0];
    const char *fqdn = fqdncache_gethostbyaddr(checklist->dst_addr, FQDN_LOOKUP_IF_MISS);

    if (fqdn) {
        checklist->dst_rdns = xstrdup(fqdn);
        return data->match(fqdn);
    } else if (!checklist->destinationDomainChecked()) {
        /* FIXME: Using AclMatchedName here is not OO correct. Should find a way to the current acl */
        debugs(28, 3, "aclMatchAcl: Can't yet compare '" << AclMatchedName << "' ACL for '" << checklist->request->GetHost() << "'");
        checklist->changeState(DestinationDomainLookup::Instance());
        return 0;
    }

    return data->match("none");
}