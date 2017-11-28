static void
externalAclHandleReply(void *data, const Helper::Reply &reply)
{
    externalAclState *state = static_cast<externalAclState *>(data);
    externalAclState *next;
    ExternalACLEntryData entryData;

    debugs(82, 2, HERE << "reply=" << reply);

    if (reply.result == Helper::Okay)
        entryData.result = ACCESS_ALLOWED;
    else if (reply.result == Helper::Error)
        entryData.result = ACCESS_DENIED;
    else //BrokenHelper,TimedOut or Unknown. Should not cached.
        entryData.result = ACCESS_DUNNO;

    // XXX: make entryData store a proper Helper::Reply object instead of copying.

    entryData.notes.append(&reply.notes);

    const char *label = reply.notes.findFirst("tag");
    if (label != NULL && *label != '\0')
        entryData.tag = label;

    label = reply.notes.findFirst("message");
    if (label != NULL && *label != '\0')
        entryData.message = label;

    label = reply.notes.findFirst("log");
    if (label != NULL && *label != '\0')
        entryData.log = label;

#if USE_AUTH
    label = reply.notes.findFirst("user");
    if (label != NULL && *label != '\0')
        entryData.user = label;

    label = reply.notes.findFirst("password");
    if (label != NULL && *label != '\0')
        entryData.password = label;
#endif

    dlinkDelete(&state->list, &state->def->queue);

    ExternalACLEntryPointer entry;
    if (cbdataReferenceValid(state->def))
        entry = external_acl_cache_add(state->def, state->key, entryData);

    do {
        void *cbdata;
        if (state->callback && cbdataReferenceValidDone(state->callback_data, &cbdata))
            state->callback(cbdata, entry);

        next = state->queue;
        state->queue = NULL;

        delete state;

        state = next;
    } while (state);
}