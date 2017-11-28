static void
parse_cachemgrpasswd(cachemgr_passwd ** head)
{
    char *passwd = NULL;
    wordlist *actions = NULL;
    cachemgr_passwd *p;
    cachemgr_passwd **P;
    parse_string(&passwd);
    parse_wordlist(&actions);
    p = static_cast<cachemgr_passwd *>(xcalloc(1, sizeof(cachemgr_passwd)));
    p->passwd = passwd;
    p->actions = actions;

    for (P = head; *P; P = &(*P)->next) {
        /*
         * See if any of the actions from this line already have a
         * password from previous lines.  The password checking
         * routines in cache_manager.c take the the password from
         * the first cachemgr_passwd struct that contains the
         * requested action.  Thus, we should warn users who might
         * think they can have two passwords for the same action.
         */
        wordlist *w;
        wordlist *u;

        for (w = (*P)->actions; w; w = w->next) {
            for (u = actions; u; u = u->next) {
                if (strcmp(w->key, u->key))
                    continue;

                debugs(0, 0, "WARNING: action '" << u->key << "' (line " << config_lineno << ") already has a password");
            }
        }
    }

    *P = p;
}