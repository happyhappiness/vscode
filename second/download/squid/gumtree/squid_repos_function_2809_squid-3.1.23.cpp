void
CacheManager::MenuAction::run(StoreEntry * sentry)
{
    CacheManagerActionList::iterator a;

    debugs(16, 4, "CacheManager::MenuCommand invoked");
    for (a = cmgr->ActionsList.begin(); a != cmgr->ActionsList.end(); ++a) {
        debugs(16, 5, "  showing action " << (*a)->action);
        storeAppendPrintf(sentry, " %-22s\t%-32s\t%s\n",
                          (*a)->action, (*a)->desc, cmgr->ActionProtection(*a));
    }
}