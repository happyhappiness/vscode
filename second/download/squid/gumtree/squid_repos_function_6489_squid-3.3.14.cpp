void
Mgr::RegisterAction(char const * action, char const * desc,
                    ClassActionCreationHandler *handler,
                    int pw_req_flag, int atomic)
{
    CacheManager::GetInstance()->registerProfile(action, desc, handler,
            pw_req_flag, atomic);
}