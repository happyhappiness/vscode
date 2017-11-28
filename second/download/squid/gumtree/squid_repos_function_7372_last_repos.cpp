void
Mgr::MenuAction::dump(StoreEntry* entry)
{
    debugs(16, 5, HERE);
    Must(entry != NULL);

    typedef CacheManager::Menu::const_iterator Iterator;
    const CacheManager::Menu& menu = CacheManager::GetInstance()->menu();

    for (Iterator a = menu.begin(); a != menu.end(); ++a) {
        storeAppendPrintf(entry, " %-22s\t%-32s\t%s\n",
                          (*a)->name, (*a)->desc,
                          CacheManager::GetInstance()->ActionProtection(*a));
    }
}