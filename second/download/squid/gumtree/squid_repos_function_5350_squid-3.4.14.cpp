void
Auth::Ntlm::UserRequest::module_start(AUTHCB * handler, void *data)
{
    static char buf[MAX_AUTHTOKEN_LEN];

    assert(data);
    assert(handler);

    if (static_cast<Auth::Ntlm::Config*>(Auth::Config::Find("ntlm"))->authenticateProgram == NULL) {
        debugs(29, DBG_CRITICAL, "ERROR: NTLM Start: no NTLM program configured.");
        handler(data);
        return;
    }

    debugs(29, 8, HERE << "credentials state is '" << user()->credentials() << "'");

    if (user()->credentials() == Auth::Pending) {
        snprintf(buf, sizeof(buf), "YR %s\n", client_blob); //CHECKME: can ever client_blob be 0 here?
    } else {
        snprintf(buf, sizeof(buf), "KK %s\n", client_blob);
    }

    waiting = 1;

    safe_free(client_blob);
    helperStatefulSubmit(ntlmauthenticators, buf, Auth::Ntlm::UserRequest::HandleReply,
                         new Auth::StateData(this, handler, data), authserver);
}