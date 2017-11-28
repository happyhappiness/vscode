    if (!strcmp(token,"any_addr"))
        addr->SetAnyAddr();
    else if ( (!strcmp(token,"no_addr")) || (!strcmp(token,"full_mask")) )
        addr->SetNoAddr();
    else if ( (*addr = token) ) // try parse numeric/IPA
        (void) 0;
    else
        addr->GetHostByName(token); // dont use ipcache
}

static void
free_address(Ip::Address *addr)
{
    addr->SetEmpty();
}

CBDATA_TYPE(acl_address);

static void
dump_acl_address(StoreEntry * entry, const char *name, acl_address * head)
{
    char buf[MAX_IPSTRLEN];
    acl_address *l;

    for (l = head; l; l = l->next) {
        if (!l->addr.IsAnyAddr())
            storeAppendPrintf(entry, "%s %s", name, l->addr.NtoA(buf,MAX_IPSTRLEN));
        else
            storeAppendPrintf(entry, "%s autoselect", name);
