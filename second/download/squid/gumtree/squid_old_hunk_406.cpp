
        state = next;
    } while (state);
}

void
ACLExternal::ExternalAclLookup(ACLChecklist *checklist, ACLExternal * me, EAH * callback, void *callback_data)
{
    MemBuf buf;
    external_acl_data *acl = me->data;
    external_acl *def = acl->def;
    externalAclState *state;
    dlink_node *node;
    externalAclState *oldstate = NULL;
    bool graceful = 0;

    ACLFilledChecklist *ch = Filled(checklist);
#if USE_AUTH
    if (acl->def->require_auth) {
        int ti;
        /* Make sure the user is authenticated */
        debugs(82, 3, "aclMatchExternal: " << acl->def->name << " check user authenticated.");

        if ((ti = AuthenticateAcl(ch)) != 1) {
            debugs(82, 1, "externalAclLookup: " << acl->def->name <<
                   " user authentication failure (" << ti << ", ch=" << ch << ")");
            callback(callback_data, NULL);
            return;
        }
        debugs(82, 3, "aclMatchExternal: " << acl->def->name << " user is authenticated.");
    }
#endif

    const char *key = makeExternalAclKey(ch, acl);

    if (!key) {
        debugs(82, 1, "externalAclLookup: lookup in '" << def->name <<
               "', prerequisit failure (ch=" << ch << ")");
        callback(callback_data, NULL);
        return;
    }

    debugs(82, 2, "externalAclLookup: lookup in '" << def->name << "' for '" << key << "'");

    external_acl_entry *entry = static_cast<external_acl_entry *>(hash_lookup(def->cache, key));

    if (entry && external_acl_entry_expired(def, entry))
        entry = NULL;

    /* Check for a pending lookup to hook into */
    // only possible if we are caching results.
    if (def->cache_size > 0) {
        for (node = def->queue.head; node; node = node->next) {
            externalAclState *oldstatetmp = static_cast<externalAclState *>(node->data);

            if (strcmp(key, oldstatetmp->key) == 0) {
                oldstate = oldstatetmp;
                break;
            }
        }
    }

    if (entry && external_acl_grace_expired(def, entry)) {
        if (oldstate) {
            debugs(82, 4, "externalAclLookup: in grace period, but already pending lookup ('" << key << "', ch=" << ch << ")");
            callback(callback_data, entry);
            return;
        } else {
            graceful = 1; // grace expired, (neg)ttl did not, and we must start a new lookup.
        }
    }

    // The entry is in the cache, grace_ttl did not expired.
    if (!graceful && entry && !external_acl_grace_expired(def, entry)) {
        /* Should not really happen, but why not.. */
        callback(callback_data, entry);
        debugs(82, 4, "externalAclLookup: no lookup pending for '" << key << "', and grace not expired");
        debugs(82, 4, "externalAclLookup: (what tha' hell?)");
        return;
    }

    /* No pending lookup found. Sumbit to helper */
    state = cbdataAlloc(externalAclState);

    state->def = cbdataReference(def);

    state->key = xstrdup(key);

    if (!graceful) {
        state->callback = callback;
        state->callback_data = cbdataReference(callback_data);
    }

    if (oldstate) {
        /* Hook into pending lookup */
        state->queue = oldstate->queue;
        oldstate->queue = state;
    } else {
        /* Check for queue overload */

        if (def->theHelper->stats.queue_size >= (int)def->theHelper->childs.n_running) {
            debugs(82, 1, "externalAclLookup: '" << def->name << "' queue overload (ch=" << ch << ")");
            cbdataFree(state);
            callback(callback_data, entry);
            return;
        }

        /* Send it off to the helper */
        buf.init();

        buf.Printf("%s\n", key);

        debugs(82, 4, "externalAclLookup: looking up for '" << key << "' in '" << def->name << "'.");

