        self_destruct();
        return;
    }

    bumpCfgStyleLast = bumpCfgStyleNow;

    aclParseAclList(LegacyParser, &A->aclList);

    acl_access *B, **T;
    for (B = *ssl_bump, T = ssl_bump; B; T = &B->next, B = B->next);
    *T = A;
}

static void dump_sslproxy_ssl_bump(StoreEntry *entry, const char *name, acl_access *ssl_bump)
{
    acl_access *sb;
    for (sb = ssl_bump; sb != NULL; sb = sb->next) {
        storeAppendPrintf(entry, "%s ", name);
        storeAppendPrintf(entry, "%s ", Ssl::bumpMode(sb->allow.kind));
        if (sb->aclList)
            dump_acl_list(entry, sb->aclList);
        storeAppendPrintf(entry, "\n");
    }
}

static void free_sslproxy_ssl_bump(acl_access **ssl_bump)
{
    free_acl_access(ssl_bump);
