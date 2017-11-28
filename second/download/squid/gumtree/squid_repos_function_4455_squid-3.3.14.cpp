int
ACLSourceDomainStrategy::match (ACLData<MatchType> * &data, ACLFilledChecklist *checklist)
{
    const char *fqdn = NULL;
    fqdn = fqdncache_gethostbyaddr(checklist->src_addr, FQDN_LOOKUP_IF_MISS);

    if (fqdn) {
        return data->match(fqdn);
    } else if (!checklist->sourceDomainChecked()) {
        /* FIXME: Using AclMatchedName here is not OO correct. Should find a way to the current acl */
        debugs(28, 3, "aclMatchAcl: Can't yet compare '" << AclMatchedName << "' ACL for '" << checklist->src_addr << "'");
        checklist->changeState(SourceDomainLookup::Instance());
        return 0;
    }

    return data->match("none");
}