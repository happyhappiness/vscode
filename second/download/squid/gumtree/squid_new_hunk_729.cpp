    storeAppendPrintf(entry, "%s %s\n", name, addr.toStr(buf,MAX_IPSTRLEN) );
}

static void
parse_address(Ip::Address *addr)
{
    char *token = ConfigParser::NextToken();

    if (!token) {
        self_destruct();
        return;
    }

