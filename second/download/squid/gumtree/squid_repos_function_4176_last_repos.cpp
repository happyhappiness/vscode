bool
ACL::matches(ACLChecklist *checklist) const
{
    PROF_start(ACL_matches);
    debugs(28, 5, "checking " << name);

    // XXX: AclMatchedName does not contain a matched ACL name when the acl
    // does not match. It contains the last (usually leaf) ACL name checked
    // (or is NULL if no ACLs were checked).
    AclMatchedName = name;

    int result = 0;
    if (!checklist->hasAle() && requiresAle()) {
        debugs(28, DBG_IMPORTANT, "WARNING: " << name << " ACL is used in " <<
               "context without an ALE state. Assuming mismatch.");
    } else if (!checklist->hasRequest() && requiresRequest()) {
        debugs(28, DBG_IMPORTANT, "WARNING: " << name << " ACL is used in " <<
               "context without an HTTP request. Assuming mismatch.");
    } else if (!checklist->hasReply() && requiresReply()) {
        debugs(28, DBG_IMPORTANT, "WARNING: " << name << " ACL is used in " <<
               "context without an HTTP response. Assuming mismatch.");
    } else {
        // make sure the ALE has as much data as possible
        if (requiresAle())
            checklist->syncAle();

        // have to cast because old match() API is missing const
        result = const_cast<ACL*>(this)->match(checklist);
    }

    const char *extra = checklist->asyncInProgress() ? " async" : "";
    debugs(28, 3, "checked: " << name << " = " << result << extra);
    PROF_stop(ACL_matches);
    return result == 1; // true for match; false for everything else
}