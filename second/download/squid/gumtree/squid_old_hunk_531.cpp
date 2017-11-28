    aclDestroyAcls(ae);
}

void
dump_acl_list(StoreEntry * entry, ACLList * head)
{
    ACLList *l;

    for (l = head; l; l = l->next) {
        storeAppendPrintf(entry, " %s%s",
                          l->op ? null_string : "!",
                          l->_acl->name);
    }
}

void
dump_acl_access(StoreEntry * entry, const char *name, acl_access * head)
{
    acl_access *l;

    for (l = head; l; l = l->next) {
        storeAppendPrintf(entry, "%s %s",
                          name,
                          l->allow ? "Allow" : "Deny");
        dump_acl_list(entry, l->aclList);
        storeAppendPrintf(entry, "\n");
    }
}

static void
parse_acl_access(acl_access ** head)
{
    aclParseAccessLine(LegacyParser, head);
}

static void
free_acl_access(acl_access ** head)
{
    aclDestroyAccessList(head);
}

static void
dump_address(StoreEntry * entry, const char *name, Ip::Address &addr)
{
    char buf[MAX_IPSTRLEN];
    storeAppendPrintf(entry, "%s %s\n", name, addr.NtoA(buf,MAX_IPSTRLEN) );
}

static void
parse_address(Ip::Address *addr)
{
    char *token = strtok(NULL, w_space);
