                          hashKeyStr(&f->hash),
                          f->flags.negcached ? 'N' : ' ',
                          f->flags.fromhosts ? 'H' : ' ',
                          ttl,
                          (int) f->name_count);

        for (k = 0; k < (int) f->name_count; ++k)
            storeAppendPrintf(sentry, " %s", f->names[k]);

        storeAppendPrintf(sentry, "\n");
    }
}

/// \ingroup FQDNCacheAPI
const char *
fqdnFromAddr(const Ip::Address &addr)
{
    const char *n;
    static char buf[MAX_IPSTRLEN];

    if (Config.onoff.log_fqdn && (n = fqdncache_gethostbyaddr(addr, 0)))
        return n;
