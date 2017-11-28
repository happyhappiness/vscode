static void
parse_acl_address(Acl::Address ** head)
{
    Acl::Address *l = new Acl::Address;
    parse_address(&l->addr);
    aclParseAclList(LegacyParser, &l->aclList, l->addr);

    Acl::Address **tail = head;
    while (*tail)
        tail = &(*tail)->next;

    *tail = l;
}