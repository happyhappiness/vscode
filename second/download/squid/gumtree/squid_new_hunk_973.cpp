static void
free_address(Ip::Address *addr)
{
    addr->setEmpty();
}

static void
dump_acl_address(StoreEntry * entry, const char *name, Acl::Address * head)
{
    char buf[MAX_IPSTRLEN];

    for (Acl::Address *l = head; l; l = l->next) {
        if (!l->addr.isAnyAddr())
            storeAppendPrintf(entry, "%s %s", name, l->addr.toStr(buf,MAX_IPSTRLEN));
        else
            storeAppendPrintf(entry, "%s autoselect", name);

        dump_acl_list(entry, l->aclList);

        storeAppendPrintf(entry, "\n");
    }
}

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

static void
free_acl_address(Acl::Address ** head)
{
    delete *head;
    *head = NULL;
}

static void
dump_acl_tos(StoreEntry * entry, const char *name, acl_tos * head)
{
    acl_tos *l;

    for (l = head; l; l = l->next) {
