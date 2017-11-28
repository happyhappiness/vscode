void
ExternalACLLookup::Start(ACLChecklist *checklist, external_acl_data *acl, bool inBackground)
{
    external_acl *def = acl->def;

    ACLFilledChecklist *ch = Filled(checklist);
    const char *key = makeExternalAclKey(ch, acl);
    assert(key);

    debugs(82, 2, HERE << (inBackground ? "bg" : "fg") << " lookup in '" <<
           def->name << "' for '" << key << "'");

    /* Check for a pending lookup to hook into */
    // only possible if we are caching results.
    externalAclState *oldstate = NULL;
    if (def->cache_size > 0) {
        for (dlink_node *node = def->queue.head; node; node = node->next) {
            externalAclState *oldstatetmp = static_cast<externalAclState *>(node->data);

            if (strcmp(key, oldstatetmp->key) == 0) {
                oldstate = oldstatetmp;
                break;
            }
        }
    }

    // A background refresh has no need to piggiback on a pending request:
    // When the pending request completes, the cache will be refreshed anyway.
    if (oldstate && inBackground) {
        debugs(82, 7, HERE << "'" << def->name << "' queue is already being refreshed (ch=" << ch << ")");
        return;
    }

    externalAclState *state = cbdataAlloc(externalAclState);
    state->def = cbdataReference(def);

    state->key = xstrdup(key);

    if (!inBackground) {
        state->callback = &ExternalACLLookup::LookupDone;
        state->callback_data = cbdataReference(checklist);
    }

    if (oldstate) {
        /* Hook into pending lookup */
        state->queue = oldstate->queue;
        oldstate->queue = state;
    } else {
        /* No pending lookup found. Sumbit to helper */

        /* Check for queue overload */

        if (def->theHelper->stats.queue_size >= (int)def->theHelper->childs.n_running) {
            debugs(82, 7, HERE << "'" << def->name << "' queue is too long");
            assert(inBackground); // or the caller should have checked
            cbdataFree(state);
            return;
        }

        /* Send it off to the helper */
        MemBuf buf;
        buf.init();

        buf.Printf("%s\n", key);

        debugs(82, 4, "externalAclLookup: looking up for '" << key << "' in '" << def->name << "'.");

        helperSubmit(def->theHelper, buf.buf, externalAclHandleReply, state);

        dlinkAdd(state, &state->list, &def->queue);

        buf.clean();
    }

    debugs(82, 4, "externalAclLookup: will wait for the result of '" << key <<
           "' in '" << def->name << "' (ch=" << ch << ").");
}