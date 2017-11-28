void
Auth::Basic::UserRequest::module_start(AUTHCB * handler, void *data)
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

        BasicAuthQueueNode *node = static_cast<BasicAuthQueueNode *>(xcalloc(1, sizeof(BasicAuthQueueNode)));
        assert(node);
        node->auth_user_request = this;
        node->handler = handler;
        node->data = cbdataReference(data);

        /* queue this validation request to be infored of the pending lookup results */
        node->next = basic_auth->auth_queue;
        basic_auth->auth_queue = node;
        return;
    }
    // otherwise submit this request to the auth helper(s) for validation

    /* mark this user as having verification in progress */
    user()->credentials(Auth::Pending);
    char buf[HELPER_INPUT_BUFFER];
    static char username[HELPER_INPUT_BUFFER];
    static char pass[HELPER_INPUT_BUFFER];
    if (static_cast<Auth::Basic::Config*>(user()->config)->utf8) {
        latin1_to_utf8(username, sizeof(username), user()->username());
        latin1_to_utf8(pass, sizeof(pass), basic_auth->passwd);
        xstrncpy(username, rfc1738_escape(username), sizeof(username));
        xstrncpy(pass, rfc1738_escape(pass), sizeof(pass));
    } else {
        xstrncpy(username, rfc1738_escape(user()->username()), sizeof(username));
        xstrncpy(pass, rfc1738_escape(basic_auth->passwd), sizeof(pass));
    }
    int sz = snprintf(buf, sizeof(buf), "%s %s\n", username, pass);
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