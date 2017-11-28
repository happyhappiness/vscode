static void
parse_cachemgrpasswd(Mgr::ActionPasswordList ** head)
{
    char *passwd = nullptr;
    parse_string(&passwd);

    Mgr::ActionPasswordList *p = new Mgr::ActionPasswordList;
    p->passwd = passwd;

    while (char *token = ConfigParser::NextQuotedToken())
        p->actions.push_back(SBuf(token));

    Mgr::ActionPasswordList **P;
    for (P = head; *P; P = &(*P)->next) {
        /*
         * See if any of the actions from this line already have a
         * password from previous lines.  The password checking
         * routines in cache_manager.c take the the password from
         * the first Mgr::ActionPasswordList that contains the
         * requested action.  Thus, we should warn users who might
         * think they can have two passwords for the same action.
         */
        for (const auto &w : (*P)->actions) {
            for (const auto &u : p->actions) {
                if (w != u)
                    continue;

                debugs(0, DBG_PARSE_NOTE(1), "ERROR: action '" << u << "' (line " << config_lineno << ") already has a password");
            }
        }
    }

    *P = p;
}