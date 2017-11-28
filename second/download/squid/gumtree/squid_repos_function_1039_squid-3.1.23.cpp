static void
parse_acl_address(acl_address ** head)
{
    acl_address *l;
    acl_address **tail = head;	/* sane name below */
    CBDATA_INIT_TYPE_FREECB(acl_address, freed_acl_address);
    l = cbdataAlloc(acl_address);
    parse_address(&l->addr);
    aclParseAclList(LegacyParser, &l->aclList);

    while (*tail)
        tail = &(*tail)->next;

    *tail = l;
}