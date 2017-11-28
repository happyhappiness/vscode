static void
parse_address(IpAddress *addr)
{
    char *token = strtok(NULL, w_space);

    if (!token) {
        self_destruct();
        return;
    }

    if (!strcmp(token,"any_addr"))
        addr->SetAnyAddr();
    else if ( (!strcmp(token,"no_addr")) || (!strcmp(token,"full_mask")) )
        addr->SetNoAddr();
    else if ( (*addr = token) ) // try parse numeric/IPA
        (void) 0;
    else
        addr->GetHostByName(token); // dont use ipcache
}