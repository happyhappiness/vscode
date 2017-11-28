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
    int sz = snprintf(buf, sizeof(buf), "%s %s\n", usern, pass);
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

void
Auth::Basic::UserRequest::HandleReply(void *data, const HelperReply &reply)
{
    Auth::StateData *r = static_cast<Auth::StateData *>(data);
    void *cbdata;
    debugs(29, 5, HERE << "reply=" << reply);

    assert(r->auth_user_request != NULL);
    assert(r->auth_user_request->user()->auth_type == Auth::AUTH_BASIC);

    // add new helper kv-pair notes to the credentials object
    // so that any transaction using those credentials can access them
    r->auth_user_request->user()->notes.appendNewOnly(&reply.notes);

    /* this is okay since we only play with the Auth::Basic::User child fields below
     * and dont pass the pointer itself anywhere */
    Auth::Basic::User *basic_auth = dynamic_cast<Auth::Basic::User *>(r->auth_user_request->user().getRaw());

    assert(basic_auth != NULL);

    if (reply.result == HelperReply::Okay)
        basic_auth->credentials(Auth::Ok);
    else {
        basic_auth->credentials(Auth::Failed);

        if (reply.other().hasContent())
            r->auth_user_request->setDenyMessage(reply.other().content());
    }

    basic_auth->expiretime = squid_curtime;

    if (cbdataReferenceValidDone(r->data, &cbdata))
        r->handler(cbdata);

    cbdataReferenceDone(r->data);

    while (basic_auth->queue) {
        if (cbdataReferenceValidDone(basic_auth->queue->data, &cbdata))
            basic_auth->queue->handler(cbdata);

        Auth::QueueNode *tmpnode = basic_auth->queue->next;
        basic_auth->queue->next = NULL;
        delete basic_auth->queue;

        basic_auth->queue = tmpnode;
    }

    delete r;
}
