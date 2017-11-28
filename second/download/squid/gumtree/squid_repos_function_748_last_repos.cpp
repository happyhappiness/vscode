static void
parse_acl_b_size_t(AclSizeLimit ** head)
{
    AclSizeLimit *l = new AclSizeLimit;

    parse_b_int64_t(&l->size);

    aclParseAclList(LegacyParser, &l->aclList, l->size);

    AclSizeLimit **tail = head; /* sane name below */
    while (*tail)
        tail = &(*tail)->next;

    *tail = l;
}