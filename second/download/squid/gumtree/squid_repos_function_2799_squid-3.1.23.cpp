CacheManagerAction *
CacheManager::findAction(char const * action)
{
    CacheManagerActionList::iterator a;

    debugs(16, 5, "CacheManager::findAction: looking for action " << action);
    for ( a = ActionsList.begin(); a != ActionsList.end(); a++) {
        if (0 == strcmp((*a)->action, action)) {
            debugs(16, 6, " found");
            return *a;
        }
    }

    debugs(16, 6, "Action not found.");
    return NULL;
}