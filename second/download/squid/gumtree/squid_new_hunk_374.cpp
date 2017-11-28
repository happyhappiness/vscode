    if (!strcmp(token,"any_addr"))
        addr->SetAnyAddr();
    else if ( (!strcmp(token,"no_addr")) || (!strcmp(token,"full_mask")) )
        addr->SetNoAddr();
    else if ( (*addr = token) ) // try parse numeric/IPA
        (void) 0;
    else if (addr->GetHostByName(token)) // dont use ipcache
        (void) 0;
    else { // not an IP and not a hostname
        debugs(3, DBG_CRITICAL, "FATAL: invalid IP address or domain name '" << token << "'");
        self_destruct();
    }
}

static void
free_address(Ip::Address *addr)
{
    addr->SetEmpty();
}

CBDATA_TYPE(AclAddress);

static void
dump_acl_address(StoreEntry * entry, const char *name, AclAddress * head)
{
    char buf[MAX_IPSTRLEN];
    AclAddress *l;

    for (l = head; l; l = l->next) {
        if (!l->addr.IsAnyAddr())
            storeAppendPrintf(entry, "%s %s", name, l->addr.NtoA(buf,MAX_IPSTRLEN));
        else
            storeAppendPrintf(entry, "%s autoselect", name);
