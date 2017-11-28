bool
ACLDomainData::match(char const *host)
{
    if (host == NULL)
        return 0;

    debugs(28, 3, "aclMatchDomainList: checking '" << host << "'");

    domains = domains->splay((char *)host, aclHostDomainCompare);

    debugs(28, 3, "aclMatchDomainList: '" << host << "' " << (splayLastResult ? "NOT found" : "found"));

    return !splayLastResult;
}