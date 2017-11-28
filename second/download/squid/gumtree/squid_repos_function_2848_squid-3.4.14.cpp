void
CacheManager::registerProfile(char const * action, char const * desc, OBJH * handler, int pw_req_flag, int atomic)
{
    debugs(16, 3, HERE << "registering legacy " << action);
    const Mgr::ActionProfile::Pointer profile = new Mgr::ActionProfile(action,
            desc, pw_req_flag, atomic, new Mgr::FunActionCreator(handler));
    registerProfile(profile);
}