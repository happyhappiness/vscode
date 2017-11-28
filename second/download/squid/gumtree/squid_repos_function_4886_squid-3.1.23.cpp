static void
authenticateBasicHandleReply(void *data, char *reply)
{
    AuthenticateStateData *r = static_cast<AuthenticateStateData *>(data);
    BasicAuthQueueNode *tmpnode;
    char *t = NULL;
    void *cbdata;
    debugs(29, 9, HERE << "{" << (reply ? reply : "<NULL>") << "}");

    if (reply) {
        if ((t = strchr(reply, ' ')))
            *t++ = '\0';

        if (*reply == '\0')
            reply = NULL;
    }

    assert(r->auth_user_request != NULL);
    assert(r->auth_user_request->user()->auth_type == AUTH_BASIC);
    basic_data *basic_auth = dynamic_cast<basic_data *>(r->auth_user_request->user());

    assert(basic_auth != NULL);

    if (reply && (strncasecmp(reply, "OK", 2) == 0))
        basic_auth->flags.credentials_ok = 1;
    else {
        basic_auth->flags.credentials_ok = 3;

        if (t && *t)
            r->auth_user_request->setDenyMessage(t);
    }

    basic_auth->credentials_checkedtime = squid_curtime;

    if (cbdataReferenceValidDone(r->data, &cbdata))
        r->handler(cbdata, NULL);

    cbdataReferenceDone(r->data);

    while (basic_auth->auth_queue) {
        tmpnode = basic_auth->auth_queue->next;

        if (cbdataReferenceValidDone(basic_auth->auth_queue->data, &cbdata))
            basic_auth->auth_queue->handler(cbdata, NULL);

        xfree(basic_auth->auth_queue);

        basic_auth->auth_queue = tmpnode;
    }

    authenticateStateFree(r);
}