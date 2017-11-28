static int
aclMatchExternal(external_acl_data *acl, ACLFilledChecklist *ch)
{
    int result;
    external_acl_entry *entry;
    const char *key = "";
    debugs(82, 9, "aclMatchExternal: acl=\"" << acl->def->name << "\"");
    entry = ch->extacl_entry;

    if (entry) {
        if (cbdataReferenceValid(entry) && entry->def == acl->def) {
            /* Ours, use it.. if the key matches */
            key = makeExternalAclKey(ch, acl);
            if (strcmp(key, (char*)entry->key) != 0) {
                debugs(82, 9, HERE << "entry key='" << (char *)entry->key << "', our key='" << key << "' dont match. Discarded.");
                // too bad. need a new lookup.
                cbdataReferenceDone(ch->extacl_entry);
                entry = NULL;
            }
        } else {
            /* Not valid, or not ours.. get rid of it */
            cbdataReferenceDone(ch->extacl_entry);
            entry = NULL;
        }
    }

    external_acl_message = "MISSING REQUIRED INFORMATION";

    if (!entry) {
        if (acl->def->require_auth) {
            int ti;
            /* Make sure the user is authenticated */

            if ((ti = AuthenticateAcl(ch)) != 1) {
                debugs(82, 2, "aclMatchExternal: " << acl->def->name << " user not authenticated (" << ti << ")");
                return ti;
            }
        }

        key = makeExternalAclKey(ch, acl);

        if (acl->def->require_auth)
            AUTHUSERREQUESTUNLOCK(ch->auth_user_request, "ACLChecklist via aclMatchExternal");

        if (!key) {
            /* Not sufficient data to process */
            return -1;
        }

        entry = static_cast<external_acl_entry *>(hash_lookup(acl->def->cache, key));

        if (!entry || external_acl_grace_expired(acl->def, entry)) {
            debugs(82, 2, "aclMatchExternal: " << acl->def->name << "(\"" << key << "\") = lookup needed");
            debugs(82, 2, "aclMatchExternal: \"" << key << "\": entry=@" <<
                   entry << ", age=" << (entry ? (long int) squid_curtime - entry->date : 0));

            if (acl->def->theHelper->stats.queue_size <= acl->def->theHelper->n_running) {
                debugs(82, 2, "aclMatchExternal: \"" << key << "\": queueing a call.");
                ch->changeState(ExternalACLLookup::Instance());
                debugs(82, 2, "aclMatchExternal: \"" << key << "\": return -1.");
                return -1; // to get here we have to have an expired cache entry. MUST not use.
            } else {
                if (!entry) {
                    debugs(82, 1, "aclMatchExternal: '" << acl->def->name <<
                           "' queue overload. Request rejected '" << key << "'.");
                    external_acl_message = "SYSTEM TOO BUSY, TRY AGAIN LATER";
                    return -1;
                } else {
                    debugs(82, 1, "aclMatchExternal: '" << acl->def->name <<
                           "' queue overload. Using stale result. '" << key << "'.");
                    /* Fall thru to processing below */
                }
            }
        }
    }

    external_acl_cache_touch(acl->def, entry);
    result = entry->result;
    external_acl_message = entry->message.termedBuf();

    debugs(82, 2, "aclMatchExternal: " << acl->def->name << " = " << result);
    copyResultsFromEntry(ch->request, entry);
    return result;
}