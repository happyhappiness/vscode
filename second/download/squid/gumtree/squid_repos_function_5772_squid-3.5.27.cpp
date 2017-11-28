Auth::UserRequest::Pointer
Auth::Config::CreateAuthUser(const char *proxy_auth, AccessLogEntry::Pointer &al)
{
    assert(proxy_auth != NULL);
    debugs(29, 9, HERE << "header = '" << proxy_auth << "'");

    Auth::Config *config = Find(proxy_auth);

    if (config == NULL || !config->active()) {
        debugs(29, (shutting_down?3:DBG_IMPORTANT), (shutting_down?"":"WARNING: ") <<
               "Unsupported or unconfigured/inactive proxy-auth scheme, '" << proxy_auth << "'");
        return NULL;
    }
    static MemBuf rmb;
    rmb.reset();
    if (config->keyExtras) {
        // %credentials and %username, which normally included in
        // request_format, are - at this time, but that is OK
        // because user name is added to key explicitly, and we do
        // not want to store authenticated credentials at all.
        config->keyExtras->assemble(rmb, al, 0);
    }

    return config->decode(proxy_auth, rmb.hasContent() ? rmb.content() : NULL);
}