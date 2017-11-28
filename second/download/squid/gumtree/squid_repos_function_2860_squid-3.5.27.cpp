Mgr::ActionProfile::Pointer
CacheManager::findAction(char const * action) const
{
    Must(action != NULL);
    Menu::const_iterator a;

    debugs(16, 5, "CacheManager::findAction: looking for action " << action);
    for (a = menu_.begin(); a != menu_.end(); ++a) {
        if (0 == strcmp((*a)->name, action)) {
            debugs(16, 6, " found");
            return *a;
        }
    }

    debugs(16, 6, "Action not found.");
    return Mgr::ActionProfilePointer();
}