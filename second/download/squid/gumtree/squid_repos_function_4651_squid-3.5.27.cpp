bool
ACLDomainData::match(char const *host)
{
    if (host == NULL)
        return 0;

    debugs(28, 3, "aclMatchDomainList: checking '" << host << "'");

    char *h = const_cast<char *>(host);
    char const * const * result = domains->find(h, aclHostDomainCompare);

    debugs(28, 3, "aclMatchDomainList: '" << host << "' " << (result ? "found" : "NOT found"));

    return (result != NULL);
}