Auth::UserRequest::Pointer
Auth::Config::CreateAuthUser(const char *proxy_auth)
{
    assert(proxy_auth != NULL);
    debugs(29, 9, HERE << "header = '" << proxy_auth << "'");

    Auth::Config *config = Find(proxy_auth);

    if (config == NULL || !config->active()) {
        debugs(29, (shutting_down?3:DBG_IMPORTANT), (shutting_down?"":"WARNING: ") <<
               "Unsupported or unconfigured/inactive proxy-auth scheme, '" << proxy_auth << "'");
        return NULL;
    }

    return config->decode(proxy_auth);
}