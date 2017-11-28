void
CacheManager::registerAction(CacheManagerAction *anAction)
{
    char *action = anAction->action;
    if (findAction(action) != NULL) {
        debugs(16, 2, "CacheManager::registerAction: Duplicate '" << action << "'. Skipping.");
        return;
    }

    assert (strstr (" ", action) == NULL);

    ActionsList += anAction;

    debugs(16, 3, "CacheManager::registerAction: registered " <<  action);
}