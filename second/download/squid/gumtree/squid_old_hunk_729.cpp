    storeAppendPrintf(entry, "%s %s\n", name, addr.toStr(buf,MAX_IPSTRLEN) );
}

static void
parse_address(Ip::Address *addr)
{
    char *token = strtok(NULL, w_space);

    if (!token) {
        self_destruct();
        return;
    }

