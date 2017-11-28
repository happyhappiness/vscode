static void parse_sslproxy_ssl_bump(acl_access **ssl_bump)
{
    typedef const char *BumpCfgStyle;
    BumpCfgStyle bcsNone = NULL;
    BumpCfgStyle bcsNew = "new client/server-first/none";
    BumpCfgStyle bcsOld = "deprecated allow/deny";
    static BumpCfgStyle bumpCfgStyleLast = bcsNone;
    BumpCfgStyle bumpCfgStyleNow = bcsNone;
    char *bm;
    if ((bm = strtok(NULL, w_space)) == NULL) {
        self_destruct();
        return;
    }

    // if this is the first rule proccessed
    if (*ssl_bump == NULL) {
        bumpCfgStyleLast = bcsNone;
        sslBumpCfgRr::lastDeprecatedRule = Ssl::bumpEnd;
    }

    allow_t action = allow_t(ACCESS_ALLOWED);

    if (strcmp(bm, Ssl::BumpModeStr[Ssl::bumpClientFirst]) == 0) {
        action.kind = Ssl::bumpClientFirst;
        bumpCfgStyleNow = bcsNew;
    } else if (strcmp(bm, Ssl::BumpModeStr[Ssl::bumpServerFirst]) == 0) {
        action.kind = Ssl::bumpServerFirst;
        bumpCfgStyleNow = bcsNew;
    } else if (strcmp(bm, Ssl::BumpModeStr[Ssl::bumpNone]) == 0) {
        action.kind = Ssl::bumpNone;
        bumpCfgStyleNow = bcsNew;
    } else if (strcmp(bm, "allow") == 0) {
        debugs(3, DBG_CRITICAL, "SECURITY NOTICE: auto-converting deprecated "
               "\"ssl_bump allow <acl>\" to \"ssl_bump client-first <acl>\" which "
               "is usually inferior to the newer server-first "
               "bumping mode. Update your ssl_bump rules.");
        action.kind = Ssl::bumpClientFirst;
        bumpCfgStyleNow = bcsOld;
        sslBumpCfgRr::lastDeprecatedRule = Ssl::bumpClientFirst;
    } else if (strcmp(bm, "deny") == 0) {
        debugs(3, DBG_CRITICAL, "WARNING: auto-converting deprecated "
               "\"ssl_bump deny <acl>\" to \"ssl_bump none <acl>\". Update "
               "your ssl_bump rules.");
        action.kind = Ssl::bumpNone;
        bumpCfgStyleNow = bcsOld;
        sslBumpCfgRr::lastDeprecatedRule = Ssl::bumpNone;
    } else {
        debugs(3, DBG_CRITICAL, "FATAL: unknown ssl_bump mode: " << bm);
        self_destruct();
        return;
    }

    if (bumpCfgStyleLast != bcsNone && bumpCfgStyleNow != bumpCfgStyleLast) {
        debugs(3, DBG_CRITICAL, "FATAL: do not mix " << bumpCfgStyleNow << " actions with " <<
               bumpCfgStyleLast << " actions. Update your ssl_bump rules.");
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