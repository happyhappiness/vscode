void
CacheManager::Start(int fd, HttpRequest * request, StoreEntry * entry)
{
    cachemgrStateData *mgr = NULL;
    ErrorState *err = NULL;
    CacheManagerAction *a;
    debugs(16, 3, "CacheManager::Start: '" << entry->url() << "'" );

    if ((mgr = ParseUrl(entry->url())) == NULL) {
        err = errorCon(ERR_INVALID_URL, HTTP_NOT_FOUND, request);
        err->url = xstrdup(entry->url());
        errorAppendEntry(entry, err);
        entry->expires = squid_curtime;
        return;
    }

    mgr->entry = entry;

    entry->lock();
    entry->expires = squid_curtime;

    debugs(16, 5, "CacheManager: " << fd_table[fd].ipaddr << " requesting '" << mgr->action << "'");

    /* get additional info from request headers */
    ParseHeaders(mgr, request);

    /* Check password */

    if (CheckPassword(mgr) != 0) {
        /* build error message */
        ErrorState *errState;
        HttpReply *rep;
        errState = errorCon(ERR_CACHE_MGR_ACCESS_DENIED, HTTP_UNAUTHORIZED, request);
        /* warn if user specified incorrect password */

        if (mgr->passwd)
            debugs(16, DBG_IMPORTANT, "CacheManager: " <<
                   (mgr->user_name ? mgr->user_name : "<unknown>") << "@" <<
                   fd_table[fd].ipaddr << ": incorrect password for '" <<
                   mgr->action << "'" );
        else
            debugs(16, DBG_IMPORTANT, "CacheManager: " <<
                   (mgr->user_name ? mgr->user_name : "<unknown>") << "@" <<
                   fd_table[fd].ipaddr << ": password needed for '" <<
                   mgr->action << "'" );

        rep = errState->BuildHttpReply();

        errorStateFree(errState);

        /*
         * add Authenticate header, use 'action' as a realm because
         * password depends on action
         */
        rep->header.putAuth("Basic", mgr->action);

        /* store the reply */
        entry->replaceHttpReply(rep);

        entry->expires = squid_curtime;

        entry->complete();

        StateFree(mgr);

        return;
    }

    debugs(16, 2, "CacheManager: " <<
           (mgr->user_name ? mgr->user_name : "<unknown>") << "@" <<
           fd_table[fd].ipaddr << " requesting '" <<
           mgr->action << "'" );
    /* retrieve object requested */
    a = findAction(mgr->action);
    assert(a != NULL);

    entry->buffer();

    {
        HttpReply *rep = new HttpReply;
        rep->setHeaders(HTTP_OK, NULL, "text/plain", -1, squid_curtime, squid_curtime);
        entry->replaceHttpReply(rep);
    }

    a->run(entry);

    entry->flush();

    if (a->flags.atomic)
        entry->complete();

    StateFree(mgr);
}