    const unsigned int chTos = tos & 0xFC;
    if (chTos != tos) {
        debugs(3, DBG_PARSE_NOTE(DBG_IMPORTANT), "WARNING: Tos value '" << tos << "' adjusted to '" << chTos << "'");
        tos = chTos;
    }

    CBDATA_INIT_TYPE_FREECB(acl_tos, freed_acl_tos);

    l = cbdataAlloc(acl_tos);

    l->tos = (tos_t)tos;

    aclParseAclList(LegacyParser, &l->aclList, token);

    while (*tail)
        tail = &(*tail)->next;

    *tail = l;
}

static void
free_acl_tos(acl_tos ** head)
{
    while (*head) {
        acl_tos *l = *head;
        *head = l->next;
        l->next = NULL;
        cbdataFree(l);
    }
}

#if SO_MARK && USE_LIBCAP

CBDATA_TYPE(acl_nfmark);

static void
dump_acl_nfmark(StoreEntry * entry, const char *name, acl_nfmark * head)
{
    acl_nfmark *l;

    for (l = head; l; l = l->next) {
        if (l->nfmark > 0)
            storeAppendPrintf(entry, "%s 0x%02X", name, l->nfmark);
        else
            storeAppendPrintf(entry, "%s none", name);

        dump_acl_list(entry, l->aclList);

        storeAppendPrintf(entry, "\n");
    }
}

static void
freed_acl_nfmark(void *data)
{
    acl_nfmark *l = static_cast<acl_nfmark *>(data);
    aclDestroyAclList(&l->aclList);
}

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
