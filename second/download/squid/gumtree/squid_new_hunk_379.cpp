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
