void
CacheManager::registerAction(char const * action, char const * desc, OBJH * handler, int pw_req_flag, int atomic)
{
    debugs(16, 3, "CacheManager::registerAction: registering legacy " <<  action);
    registerAction(new CacheManagerActionLegacy(action,desc,pw_req_flag,atomic,handler));
}