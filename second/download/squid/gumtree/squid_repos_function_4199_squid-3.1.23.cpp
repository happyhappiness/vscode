void
aclParseArpList(SplayNode<acl_arp_data *> **curlist)
{
    char *t = NULL;
    SplayNode<acl_arp_data *> **Top = curlist;
    acl_arp_data *q = NULL;

    while ((t = strtokFile())) {
        if ((q = aclParseArpData(t)) == NULL)
            continue;

        *Top = (*Top)->insert(q, aclArpCompare);
    }
}