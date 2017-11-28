static void
parse_acl_nfmark(acl_nfmark ** head)
{
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

    acl_nfmark *l = new acl_nfmark;

    l->nfmark = mark;

    aclParseAclList(LegacyParser, &l->aclList, token);

    acl_nfmark **tail = head;   /* sane name below */
    while (*tail)
        tail = &(*tail)->next;

    *tail = l;
}