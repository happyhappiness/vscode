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