        self_destruct();
        return;
    }

    bumpCfgStyleLast = bumpCfgStyleNow;

    Acl::AndNode *rule = new Acl::AndNode;
    rule->context("(ssl_bump rule)", config_input_line);
    rule->lineParse();
    // empty rule OK

    assert(ssl_bump);
    if (!*ssl_bump) {
        *ssl_bump = new Acl::Tree;
        (*ssl_bump)->context("(ssl_bump rules)", config_input_line);
    }

    (*ssl_bump)->add(rule, action);
}

static void dump_sslproxy_ssl_bump(StoreEntry *entry, const char *name, acl_access *ssl_bump)
{
    if (ssl_bump) {
        wordlist *lines = ssl_bump->treeDump(name, Ssl::BumpModeStr);
        dump_wordlist(entry, lines);
        wordlistDestroy(&lines);
    }
}

static void free_sslproxy_ssl_bump(acl_access **ssl_bump)
{
    free_acl_access(ssl_bump);
