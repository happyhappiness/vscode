static void
parse_acl_b_size_t(acl_size_t ** head)
{
    acl_size_t *l;
    acl_size_t **tail = head;	/* sane name below */

    CBDATA_INIT_TYPE_FREECB(acl_size_t, freed_acl_b_size_t);

    l = cbdataAlloc(acl_size_t);

    parse_b_int64_t(&l->size);

    aclParseAclList(LegacyParser, &l->aclList);

    while (*tail)
        tail = &(*tail)->next;

    *tail = l;
}