void
CacheManager::registerProfile(char const * action, char const * desc,
                              ClassActionCreator::Handler *handler,
                              int pw_req_flag, int atomic)
{
    const Mgr::ActionProfile::Pointer profile = new Mgr::ActionProfile(action,
            desc, pw_req_flag, atomic, new ClassActionCreator(handler));
    registerProfile(profile);
}