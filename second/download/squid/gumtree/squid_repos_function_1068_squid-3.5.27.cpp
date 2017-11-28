static void
parse_address(Ip::Address *addr)
{
    char *token = ConfigParser::NextToken();

    if (!token) {
        self_destruct();
        return;
    }

    if (!strcmp(token,"any_addr"))
        addr->setAnyAddr();
    else if ( (!strcmp(token,"no_addr")) || (!strcmp(token,"full_mask")) )
        addr->setNoAddr();
    else if ( (*addr = token) ) // try parse numeric/IPA
        (void) 0;
    else if (addr->GetHostByName(token)) // dont use ipcache
        (void) 0;
    else { // not an IP and not a hostname
        debugs(3, DBG_CRITICAL, "FATAL: invalid IP address or domain name '" << token << "'");
        self_destruct();
    }
}