void
authenticateShutdown(void)
{
    debugs(29, 2, "authenticateShutdown: shutting down auth schemes");
    /* free the cache if we are shutting down */

    if (shutting_down) {
        hashFreeItems(proxy_auth_username_cache, AuthUserHashPointer::removeFromCache);
        AuthScheme::FreeAll();
    } else {
        for (AuthScheme::const_iterator i = AuthScheme::Schemes().begin(); i != AuthScheme::Schemes().end(); ++i)
            (*i)->done();
    }
}