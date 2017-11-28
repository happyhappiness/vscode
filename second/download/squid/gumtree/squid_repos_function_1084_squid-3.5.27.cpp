static void
parse_acl_b_size_t(AclSizeLimit ** head)
{
    AclSizeLimit *l;
    AclSizeLimit **tail = head; /* sane name below */

    CBDATA_INIT_TYPE_FREECB(AclSizeLimit, freed_acl_b_size_t);

    l = cbdataAlloc(AclSizeLimit);

    parse_b_int64_t(&l->size);

    aclParseAclList(LegacyParser, &l->aclList, l->size);

    while (*tail)
        tail = &(*tail)->next;

    *tail = l;
}