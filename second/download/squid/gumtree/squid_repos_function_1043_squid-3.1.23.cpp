static void
parse_acl_tos(acl_tos ** head)
{
    acl_tos *l;
    acl_tos **tail = head;	/* sane name below */
    int tos;
    char junk;
    char *token = strtok(NULL, w_space);

    if (!token) {
        self_destruct();
        return;
    }

    if (sscanf(token, "0x%x%c", &tos, &junk) != 1) {
        self_destruct();
        return;
    }

    if (tos < 0 || tos > 255) {
        self_destruct();
        return;
    }

    CBDATA_INIT_TYPE_FREECB(acl_tos, freed_acl_tos);

    l = cbdataAlloc(acl_tos);

    l->tos = tos;

    aclParseAclList(LegacyParser, &l->aclList);

    while (*tail)
        tail = &(*tail)->next;

    *tail = l;
}