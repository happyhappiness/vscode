static allow_t
aclMatchExternal(external_acl_data *acl, ACLFilledChecklist *ch)
{
    debugs(82, 9, HERE << "acl=\"" << acl->def->name << "\"");
    ExternalACLEntryPointer entry = ch->extacl_entry;

    external_acl_message = "MISSING REQUIRED INFORMATION";

    if (entry != NULL) {
        if (entry->def == acl->def) {
            /* Ours, use it.. if the key matches */
            const char *key = makeExternalAclKey(ch, acl);
            if (!key)
                return ACCESS_DUNNO; // insufficent data to continue
            if (strcmp(key, (char*)entry->key) != 0) {
                debugs(82, 9, "entry key='" << (char *)entry->key << "', our key='" << key << "' dont match. Discarded.");
                // too bad. need a new lookup.
                entry = ch->extacl_entry = NULL;
            }
        } else {
            /* Not ours.. get rid of it */
            debugs(82, 9, "entry " << entry << " not valid or not ours. Discarded.");
            if (entry != NULL) {
                debugs(82, 9, "entry def=" << entry->def << ", our def=" << acl->def);
                const char *key = makeExternalAclKey(ch, acl); // may be nil
                debugs(82, 9, "entry key='" << (char *)entry->key << "', our key='" << key << "'");
            }
            entry = ch->extacl_entry = NULL;
        }
    }

    if (!entry) {
        debugs(82, 9, HERE << "No helper entry available");
#if USE_AUTH
        if (acl->def->require_auth) {
            /* Make sure the user is authenticated */
            debugs(82, 3, HERE << acl->def->name << " check user authenticated.");
            const allow_t ti = AuthenticateAcl(ch);
            if (!ti.allowed()) {
                debugs(82, 2, HERE << acl->def->name << " user not authenticated (" << ti << ")");
                return ti;
            }
            debugs(82, 3, HERE << acl->def->name << " user is authenticated.");
        }
#endif
        const char *key = makeExternalAclKey(ch, acl);

        if (!key) {
            /* Not sufficient data to process */
            return ACCESS_DUNNO;
        }

        entry = static_cast<ExternalACLEntry *>(hash_lookup(acl->def->cache, key));

        const ExternalACLEntryPointer staleEntry = entry;
        if (entry != NULL && external_acl_entry_expired(acl->def, entry))
            entry = NULL;

        if (entry != NULL && external_acl_grace_expired(acl->def, entry)) {
            // refresh in the background
            ExternalACLLookup::Start(ch, acl, true);
            debugs(82, 4, HERE << "no need to wait for the refresh of '" <<
                   key << "' in '" << acl->def->name << "' (ch=" << ch << ").");
        }

        if (!entry) {
            debugs(82, 2, HERE << acl->def->name << "(\"" << key << "\") = lookup needed");

            // TODO: All other helpers allow temporary overload. Should not we?
            if (!acl->def->theHelper->willOverload()) {
                debugs(82, 2, HERE << "\"" << key << "\": queueing a call.");
                if (!ch->goAsync(ExternalACLLookup::Instance()))
                    debugs(82, 2, "\"" << key << "\": no async support!");
                debugs(82, 2, HERE << "\"" << key << "\": return -1.");
                return ACCESS_DUNNO; // expired cached or simply absent entry
            } else {
                if (!staleEntry) {
                    debugs(82, DBG_IMPORTANT, "WARNING: external ACL '" << acl->def->name <<
                           "' queue full. Request rejected '" << key << "'.");
                    external_acl_message = "SYSTEM TOO BUSY, TRY AGAIN LATER";
                    return ACCESS_DUNNO;
                } else {
                    debugs(82, DBG_IMPORTANT, "WARNING: external ACL '" << acl->def->name <<
                           "' queue full. Using stale result. '" << key << "'.");
                    entry = staleEntry;
                    /* Fall thru to processing below */
                }
            }
        }
    }

    debugs(82, 4, HERE << "entry = { date=" <<
           (long unsigned int) entry->date <<
           ", result=" << entry->result <<
           " tag=" << entry->tag <<
           " log=" << entry->log << " }");
#if USE_AUTH
    debugs(82, 4, HERE << "entry user=" << entry->user);
#endif

    external_acl_cache_touch(acl->def, entry);
    external_acl_message = entry->message.termedBuf();

    debugs(82, 2, HERE << acl->def->name << " = " << entry->result);
    copyResultsFromEntry(ch->request, entry);
    return entry->result;
}