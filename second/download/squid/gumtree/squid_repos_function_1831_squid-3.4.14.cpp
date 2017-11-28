static void
externalAclHandleReply(void *data, const HelperReply &reply)
{
    externalAclState *state = static_cast<externalAclState *>(data);
    externalAclState *next;
    ExternalACLEntryData entryData;
    entryData.result = ACCESS_DENIED;

    debugs(82, 2, HERE << "reply=" << reply);

    if (reply.result == HelperReply::Okay)
        entryData.result = ACCESS_ALLOWED;
    // XXX: handle other non-DENIED results better

    // XXX: make entryData store a proper HelperReply object instead of copying.

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
    if (cbdataReferenceValid(state->def)) {
        // only cache OK and ERR results.
        if (reply.result == HelperReply::Okay || reply.result == HelperReply::Error)
            entry = external_acl_cache_add(state->def, state->key, entryData);
        else {
            const ExternalACLEntryPointer oldentry = static_cast<ExternalACLEntry *>(hash_lookup(state->def->cache, state->key));

            if (oldentry != NULL)
                external_acl_cache_delete(state->def, oldentry);
        }
    }

    do {
        void *cbdata;
        cbdataReferenceDone(state->def);

        if (state->callback && cbdataReferenceValidDone(state->callback_data, &cbdata))
            state->callback(cbdata, entry);

        next = state->queue;

        cbdataFree(state);

        state = next;
    } while (state);
}