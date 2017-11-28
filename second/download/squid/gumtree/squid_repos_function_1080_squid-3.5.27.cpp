static void
parse_acl_nfmark(acl_nfmark ** head)
{
    acl_nfmark *l;
    acl_nfmark **tail = head;   /* sane name below */
    nfmark_t mark;
    char *token = ConfigParser::NextToken();

    if (!token) {
        self_destruct();
        return;
    }

    if (!xstrtoui(token, NULL, &mark, 0, std::numeric_limits<nfmark_t>::max())) {
        self_destruct();
        return;
    }

    CBDATA_INIT_TYPE_FREECB(acl_nfmark, freed_acl_nfmark);

    l = cbdataAlloc(acl_nfmark);

    l->nfmark = mark;

    aclParseAclList(LegacyParser, &l->aclList, token);

    while (*tail)
        tail = &(*tail)->next;

    *tail = l;
}