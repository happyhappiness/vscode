void
Auth::Digest::UserRequest::startHelperLookup(HttpRequest *request, AccessLogEntry::Pointer &al, AUTHCB * handler, void *data)
{
    char buf[8192];

    assert(user() != NULL && user()->auth_type == Auth::AUTH_DIGEST);
    debugs(29, 9, HERE << "'\"" << user()->username() << "\":\"" << realm << "\"'");

    if (static_cast<Auth::Digest::Config*>(Auth::Config::Find("digest"))->authenticateProgram == NULL) {
        debugs(29, DBG_CRITICAL, "ERROR: No Digest authentication program configured.");
        handler(data);
        return;
    }

    const char *keyExtras = helperRequestKeyExtras(request, al);
    if (static_cast<Auth::Digest::Config*>(Auth::Config::Find("digest"))->utf8) {
        char userstr[1024];
        latin1_to_utf8(userstr, sizeof(userstr), user()->username());
        if (keyExtras)
            snprintf(buf, 8192, "\"%s\":\"%s\" %s\n", userstr, realm, keyExtras);
        else
            snprintf(buf, 8192, "\"%s\":\"%s\"\n", userstr, realm);
    } else {
        if (keyExtras)
            snprintf(buf, 8192, "\"%s\":\"%s\" %s\n", user()->username(), realm, keyExtras);
        else
            snprintf(buf, 8192, "\"%s\":\"%s\"\n", user()->username(), realm);
    }

    helperSubmit(digestauthenticators, buf, Auth::Digest::UserRequest::HandleReply,
                 new Auth::StateData(this, handler, data));
}