    peerClearRRStart();
}

static void
free_peer(CachePeer ** P)
{
    CachePeer *p;

    while ((p = *P) != NULL) {
        *P = p->next;
#if USE_CACHE_DIGESTS

        cbdataReferenceDone(p->digest);
#endif

        // the mgr job will notice that its owner is gone and stop
        PeerPoolMgr::Checkpoint(p->standby.mgr, "peer gone");
        delete p->standby.pool;
        cbdataFree(p);
    }

    Config.npeers = 0;
}

static void
dump_cachemgrpasswd(StoreEntry * entry, const char *name, Mgr::ActionPasswordList * list)
{
    wordlist *w;

    while (list != NULL) {
        if (strcmp(list->passwd, "none") && strcmp(list->passwd, "disable"))
            storeAppendPrintf(entry, "%s XXXXXXXXXX", name);
        else
            storeAppendPrintf(entry, "%s %s", name, list->passwd);

        for (w = list->actions; w != NULL; w = w->next) {
            storeAppendPrintf(entry, " %s", w->key);
        }

        storeAppendPrintf(entry, "\n");
        list = list->next;
    }
}

static void
parse_cachemgrpasswd(Mgr::ActionPasswordList ** head)
{
    char *passwd = NULL;
    wordlist *actions = NULL;
    Mgr::ActionPasswordList *p;
    Mgr::ActionPasswordList **P;
    parse_string(&passwd);
    parse_wordlist(&actions);
    p = new Mgr::ActionPasswordList;
    p->passwd = passwd;
    p->actions = actions;

    for (P = head; *P; P = &(*P)->next) {
        /*
         * See if any of the actions from this line already have a
         * password from previous lines.  The password checking
         * routines in cache_manager.c take the the password from
         * the first Mgr::ActionPasswordList that contains the
         * requested action.  Thus, we should warn users who might
         * think they can have two passwords for the same action.
         */
        wordlist *w;
        wordlist *u;

        for (w = (*P)->actions; w; w = w->next) {
            for (u = actions; u; u = u->next) {
                if (strcmp(w->key, u->key))
                    continue;

                debugs(0, DBG_CRITICAL, "WARNING: action '" << u->key << "' (line " << config_lineno << ") already has a password");
            }
        }
    }

    *P = p;
}

static void
free_cachemgrpasswd(Mgr::ActionPasswordList ** head)
{
    Mgr::ActionPasswordList *p;

    while ((p = *head) != NULL) {
        *head = p->next;
        xfree(p->passwd);
        wordlistDestroy(&p->actions);
        xfree(p);
    }
}

static void
dump_denyinfo(StoreEntry * entry, const char *name, AclDenyInfoList * var)
{
    AclNameList *a;

    while (var != NULL) {
        storeAppendPrintf(entry, "%s %s", name, var->err_page_name);

        for (a = var->acl_list; a != NULL; a = a->next)
            storeAppendPrintf(entry, " %s", a->name);

        storeAppendPrintf(entry, "\n");

        var = var->next;
    }
