void
Auth::Negotiate::UserRequest::startHelperLookup(HttpRequest *req, AccessLogEntry::Pointer &al, AUTHCB * handler, void *data)
{
    static char buf[MAX_AUTHTOKEN_LEN];

    assert(data);
    assert(handler);

    assert(user() != NULL);
    assert(user()->auth_type == Auth::AUTH_NEGOTIATE);

    if (static_cast<Auth::Negotiate::Config*>(Auth::Config::Find("negotiate"))->authenticateProgram == NULL) {
        debugs(29, DBG_CRITICAL, "ERROR: No Negotiate authentication program configured.");
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

    if (printResult < 0 || printResult >= (int)sizeof(buf)) {
        if (printResult < 0)
            debugs(29, DBG_CRITICAL, "ERROR: Can not build negotiate authentication helper request");
        else
            debugs(29, DBG_CRITICAL, "ERROR: Negotiate authentication helper request too big for the " << sizeof(buf) << "-byte buffer");
        handler(data);
        return;
    }

    waiting = 1;

    safe_free(client_blob);

    helperStatefulSubmit(negotiateauthenticators, buf, Auth::Negotiate::UserRequest::HandleReply,
                         new Auth::StateData(this, handler, data), authserver);
}