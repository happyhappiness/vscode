
        storeAppendPrintf(sentry, "\n");
    }
}

/// \ingroup FQDNCacheAPI
const char *
fqdnFromAddr(const Ip::Address &addr)
{
    const char *n;
    static char buf[MAX_IPSTRLEN];

