void
Auth::Ntlm::UserRequest::startHelperLookup(HttpRequest *req, AccessLogEntry::Pointer &al, AUTHCB * handler, void *data)
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

    const char *keyExtras = helperRequestKeyExtras(request, al);
    int printResult = 0;
    if (user()->credentials() == Auth::Pending) {
        if (keyExtras)
            printResult = snprintf(buf, sizeof(buf), "YR %s %s\n", client_blob, keyExtras);
        else
            printResult = snprintf(buf, sizeof(buf), "YR %s\n", client_blob); //CHECKME: can ever client_blob be 0 here?
    } else {
        if (keyExtras)
            printResult = snprintf(buf, sizeof(buf), "KK %s %s\n", client_blob, keyExtras);
        else
            printResult = snprintf(buf, sizeof(buf), "KK %s\n", client_blob);
    }
    waiting = 1;

    if (printResult < 0 || printResult >= (int)sizeof(buf)) {
        if (printResult < 0)
            debugs(29, DBG_CRITICAL, "ERROR: Can not build ntlm authentication helper request");
        else
            debugs(29, DBG_CRITICAL, "ERROR: Ntlm authentication helper request too big for the " << sizeof(buf) << "-byte buffer.");
        handler(data);
        return;
    }

    safe_free(client_blob);
    helperStatefulSubmit(ntlmauthenticators, buf, Auth::Ntlm::UserRequest::HandleReply,
                         new Auth::StateData(this, handler, data), authserver);
}