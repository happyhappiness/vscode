void
ACLDomainData::parse()
{
    if (!domains)
        domains = new Splay<char *>();

    while (char *t = ConfigParser::strtokFile()) {
        Tolower(t);
        domains->insert(xstrdup(t), aclDomainCompare);
    }
}