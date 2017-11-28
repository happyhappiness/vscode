    const unsigned int chTos = tos & 0xFC;
    if (chTos != tos) {
        debugs(3, DBG_PARSE_NOTE(DBG_IMPORTANT), "WARNING: Tos value '" << tos << "' adjusted to '" << chTos << "'");
        tos = chTos;
    }

    acl_tos *l = new acl_tos;

    l->tos = (tos_t)tos;

    aclParseAclList(LegacyParser, &l->aclList, token);

    acl_tos **tail = head;  /* sane name below */
    while (*tail)
        tail = &(*tail)->next;

    *tail = l;
}

static void
free_acl_tos(acl_tos ** head)
{
    delete *head;
    *head = NULL;
}

#if SO_MARK && USE_LIBCAP

static void
dump_acl_nfmark(StoreEntry * entry, const char *name, acl_nfmark * head)
{
    for (acl_nfmark *l = head; l; l = l->next) {
        if (l->nfmark > 0)
            storeAppendPrintf(entry, "%s 0x%02X", name, l->nfmark);
        else
            storeAppendPrintf(entry, "%s none", name);

        dump_acl_list(entry, l->aclList);

        storeAppendPrintf(entry, "\n");
    }
}

static void
parse_acl_nfmark(acl_nfmark ** head)
{
    nfmark_t mark;
    char *token = ConfigParser::NextToken();

    if (!token) {
        self_destruct();
        return;
