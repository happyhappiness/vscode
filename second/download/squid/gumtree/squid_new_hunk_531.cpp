    aclDestroyAcls(ae);
}

void
dump_acl_list(StoreEntry * entry, ACLList * head)
{
    wordlist *values = head->dump();
    dump_wordlist(entry, values);
    wordlistDestroy(&values);
}

void
dump_acl_access(StoreEntry * entry, const char *name, acl_access * head)
{
    if (head) {
        wordlist *lines = head->treeDump(name, NULL);
        dump_wordlist(entry, lines);
        wordlistDestroy(&lines);
    }
}

static void
parse_acl_access(acl_access ** head)
{
    aclParseAccessLine(cfg_directive, LegacyParser, head);
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
    storeAppendPrintf(entry, "%s %s\n", name, addr.toStr(buf,MAX_IPSTRLEN) );
}

static void
parse_address(Ip::Address *addr)
{
    char *token = strtok(NULL, w_space);
