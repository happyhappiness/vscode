static void
parse_acl_address(AclAddress ** head)
{
    AclAddress *l;
    AclAddress **tail = head;	/* sane name below */
    CBDATA_INIT_TYPE_FREECB(AclAddress, freed_acl_address);
    l = cbdataAlloc(AclAddress);
    parse_address(&l->addr);
    aclParseAclList(LegacyParser, &l->aclList);

    while (*tail)
        tail = &(*tail)->next;

    *tail = l;
}