static void
free_address(Ip::Address *addr)
{
    addr->setEmpty();
}

CBDATA_TYPE(AclAddress);

static void
dump_acl_address(StoreEntry * entry, const char *name, AclAddress * head)
{
    char buf[MAX_IPSTRLEN];
    AclAddress *l;

    for (l = head; l; l = l->next) {
        if (!l->addr.isAnyAddr())
            storeAppendPrintf(entry, "%s %s", name, l->addr.toStr(buf,MAX_IPSTRLEN));
        else
            storeAppendPrintf(entry, "%s autoselect", name);

        dump_acl_list(entry, l->aclList);

        storeAppendPrintf(entry, "\n");
    }
}

static void
freed_acl_address(void *data)
{
    AclAddress *l = static_cast<AclAddress *>(data);
    aclDestroyAclList(&l->aclList);
}

static void
parse_acl_address(AclAddress ** head)
{
    AclAddress *l;
    AclAddress **tail = head;   /* sane name below */
    CBDATA_INIT_TYPE_FREECB(AclAddress, freed_acl_address);
    l = cbdataAlloc(AclAddress);
    parse_address(&l->addr);
    aclParseAclList(LegacyParser, &l->aclList, l->addr);

    while (*tail)
        tail = &(*tail)->next;

    *tail = l;
}

static void
free_acl_address(AclAddress ** head)
{
    while (*head) {
        AclAddress *l = *head;
        *head = l->next;
        cbdataFree(l);
    }
}

CBDATA_TYPE(acl_tos);

static void
dump_acl_tos(StoreEntry * entry, const char *name, acl_tos * head)
{
    acl_tos *l;

    for (l = head; l; l = l->next) {
