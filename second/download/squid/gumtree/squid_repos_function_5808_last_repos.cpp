void
Auth::Basic::UserRequest::startHelperLookup(HttpRequest *request, AccessLogEntry::Pointer &al, AUTHCB * handler, void *data)
{
    assert(user()->auth_type == Auth::AUTH_BASIC);
    Auth::Basic::User *basic_auth = dynamic_cast<Auth::Basic::User *>(user().getRaw());
    assert(basic_auth != NULL);
    debugs(29, 9, HERE << "'" << basic_auth->username() << ":" << basic_auth->passwd << "'");

    if (static_cast<Auth::Basic::Config*>(Auth::Config::Find("basic"))->authenticateProgram == NULL) {
        debugs(29, DBG_CRITICAL, "ERROR: No Basic authentication program configured.");
        handler(data);
        return;
    }

    /* check to see if the auth_user already has a request outstanding */
    if (user()->credentials() == Auth::Pending) {
        /* there is a request with the same credentials already being verified */

        Auth::QueueNode *node = new Auth::QueueNode(this, handler, data);

        /* queue this validation request to be infored of the pending lookup results */
        node->next = basic_auth->queue;
        basic_auth->queue = node;
        return;
    }
    // otherwise submit this request to the auth helper(s) for validation

    /* mark this user as having verification in progress */
    user()->credentials(Auth::Pending);
    char buf[HELPER_INPUT_BUFFER];
    static char usern[HELPER_INPUT_BUFFER];
    static char pass[HELPER_INPUT_BUFFER];
    if (static_cast<Auth::Basic::Config*>(user()->config)->utf8) {
        latin1_to_utf8(usern, sizeof(usern), user()->username());
        latin1_to_utf8(pass, sizeof(pass), basic_auth->passwd);
        xstrncpy(usern, rfc1738_escape(usern), sizeof(usern));
        xstrncpy(pass, rfc1738_escape(pass), sizeof(pass));
    } else {
        xstrncpy(usern, rfc1738_escape(user()->username()), sizeof(usern));
        xstrncpy(pass, rfc1738_escape(basic_auth->passwd), sizeof(pass));
    }
    int sz = 0;
    if (const char *keyExtras = helperRequestKeyExtras(request, al))
        sz = snprintf(buf, sizeof(buf), "%s %s %s\n", usern, pass, keyExtras);
    else
        sz = snprintf(buf, sizeof(buf), "%s %s\n", usern, pass);

    if (sz<=0) {
        debugs(9, DBG_CRITICAL, "ERROR: Basic Authentication Failure. Can not build helper validation request.");
        handler(data);
    } else if (static_cast<size_t>(sz) >= sizeof(buf)) {
        debugs(9, DBG_CRITICAL, "ERROR: Basic Authentication Failure. user:password exceeds " << sizeof(buf) << " bytes.");
        handler(data);
    } else
        helperSubmit(basicauthenticators, buf, Auth::Basic::UserRequest::HandleReply,
                     new Auth::StateData(this, handler, data));
}