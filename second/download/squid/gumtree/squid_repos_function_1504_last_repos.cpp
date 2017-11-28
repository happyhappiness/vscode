void
ExternalACLLookup::Start(ACLChecklist *checklist, external_acl_data *acl, bool inBackground)
{
    external_acl *def = acl->def;

    ACLFilledChecklist *ch = Filled(checklist);
    const char *key = makeExternalAclKey(ch, acl);
    assert(key); // XXX: will fail if EXT_ACL_IDENT case needs an async lookup

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

    externalAclState *state = new externalAclState(def, key);

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

        MemBuf buf;
        buf.init();
        buf.appendf("%s\n", key);
        debugs(82, 4, "externalAclLookup: looking up for '" << key << "' in '" << def->name << "'.");

        if (!def->theHelper->trySubmit(buf.buf, externalAclHandleReply, state)) {
            debugs(82, 7, HERE << "'" << def->name << "' submit to helper failed");
            assert(inBackground); // or the caller should have checked
            delete state;
            return;
        }

        dlinkAdd(state, &state->list, &def->queue);

        buf.clean();
    }

    debugs(82, 4, "externalAclLookup: will wait for the result of '" << key <<
           "' in '" << def->name << "' (ch=" << ch << ").");
}