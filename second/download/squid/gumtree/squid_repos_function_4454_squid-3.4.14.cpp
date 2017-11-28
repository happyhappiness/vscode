void
ACLDomainData::parse()
{
    char *t = NULL;

    while ((t = strtokFile())) {
        Tolower(t);
        domains = domains->insert(xstrdup(t), aclDomainCompare);
    }
}