void
Auth::Basic::UserRequest::HandleReply(void *data, char *reply)
{
    Auth::StateData *r = static_cast<Auth::StateData *>(data);
    BasicAuthQueueNode *tmpnode;
    char *t = NULL;
    void *cbdata;
    debugs(29, 5, HERE << "{" << (reply ? reply : "<NULL>") << "}");

    if (reply) {
        if ((t = strchr(reply, ' '))) {
            *t = '\0';
            ++t;
        }

        if (*reply == '\0')
            reply = NULL;
    }

    assert(r->auth_user_request != NULL);
    assert(r->auth_user_request->user()->auth_type == Auth::AUTH_BASIC);

    /* this is okay since we only play with the Auth::Basic::User child fields below
     * and dont pass the pointer itself anywhere */
    Auth::Basic::User *basic_auth = dynamic_cast<Auth::Basic::User *>(r->auth_user_request->user().getRaw());

    assert(basic_auth != NULL);

    if (reply && (strncasecmp(reply, "OK", 2) == 0))
        basic_auth->credentials(Auth::Ok);
    else {
        basic_auth->credentials(Auth::Failed);

        if (t && *t)
            r->auth_user_request->setDenyMessage(t);
    }

    basic_auth->expiretime = squid_curtime;

    if (cbdataReferenceValidDone(r->data, &cbdata))
        r->handler(cbdata);

    cbdataReferenceDone(r->data);

    while (basic_auth->auth_queue) {
        tmpnode = basic_auth->auth_queue->next;

        if (cbdataReferenceValidDone(basic_auth->auth_queue->data, &cbdata))
            basic_auth->auth_queue->handler(cbdata);

        xfree(basic_auth->auth_queue);

        basic_auth->auth_queue = tmpnode;
    }

    delete r;
}