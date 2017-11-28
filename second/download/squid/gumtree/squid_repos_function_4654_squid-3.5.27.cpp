void
ACLDomainData::parse()
{
    char *t = NULL;

    if (!domains)
        domains = new Splay<char *>();

    while ((t = strtokFile())) {
        Tolower(t);
        domains->insert(xstrdup(t), aclDomainCompare);
    }
}