static void
externalAclHandleReply(void *data, char *reply)
{
    externalAclState *state = static_cast<externalAclState *>(data);
    externalAclState *next;
    char *status;
    char *token;
    char *value;
    char *t;
    ExternalACLEntryData entryData;
    entryData.result = 0;
    external_acl_entry *entry = NULL;

    debugs(82, 2, "externalAclHandleReply: reply=\"" << reply << "\"");

    if (reply) {
        status = strwordtok(reply, &t);

        if (status && strcmp(status, "OK") == 0)
            entryData.result = 1;

        while ((token = strwordtok(NULL, &t))) {
            value = strchr(token, '=');

            if (value) {
                *value++ = '\0';	/* terminate the token, and move up to the value */

                if (state->def->quote == external_acl::QUOTE_METHOD_URL)
                    rfc1738_unescape(value);

                if (strcmp(token, "user") == 0)
                    entryData.user = value;
                else if (strcmp(token, "message") == 0)
                    entryData.message = value;
                else if (strcmp(token, "error") == 0)
                    entryData.message = value;
                else if (strcmp(token, "tag") == 0)
                    entryData.tag = value;
                else if (strcmp(token, "log") == 0)
                    entryData.log = value;
                else if (strcmp(token, "password") == 0)
                    entryData.password = value;
                else if (strcmp(token, "passwd") == 0)
                    entryData.password = value;
                else if (strcmp(token, "login") == 0)
                    entryData.user = value;
            }
        }
    }

    dlinkDelete(&state->list, &state->def->queue);

    if (cbdataReferenceValid(state->def)) {
        if (reply)
            entry = external_acl_cache_add(state->def, state->key, entryData);
        else {
            external_acl_entry *oldentry = (external_acl_entry *)hash_lookup(state->def->cache, state->key);

            if (oldentry)
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