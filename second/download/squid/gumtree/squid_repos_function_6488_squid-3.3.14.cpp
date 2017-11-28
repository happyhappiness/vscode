void
Mgr::RegisterAction(char const * action, char const * desc,
                    OBJH * handler,
                    int pw_req_flag, int atomic)
{
    CacheManager::GetInstance()->registerProfile(action, desc, handler,
            pw_req_flag, atomic);
}