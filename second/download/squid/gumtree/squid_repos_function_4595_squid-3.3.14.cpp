bool
ACLList::matches (ACLChecklist *checklist) const
{
    assert (_acl);
    // XXX: AclMatchedName does not contain a matched ACL name when the acl
    // does not match (or contains stale name if no ACLs are checked). In
    // either case, we get misleading debugging and possibly incorrect error
    // messages. Unfortunately, deny_info's "when none http_access
    // lines match" exception essentially requires this mess.
    // TODO: Rework by using an acl-free deny_info for the no-match cases?
    AclMatchedName = _acl->name;
    debugs(28, 3, "ACLList::matches: checking " << (op ? null_string : "!") << _acl->name);

    bool result = false;
    if (_acl->checklistMatches(checklist) == 1) {
        debugs(28, 5, _acl->name << " matched" << (op ? "." : ", negating."));
        result = (op != 0);
    } else if (checklist->finished()) {
        debugs(28, 5, _acl->name << " failed.");
        result = false;
    } else if (checklist->asyncNeeded()) {
        debugs(28, 5, _acl->name << " needs async lookup");
        result = false;
    } else {
        debugs(28, 5, _acl->name << " mismatched" << (op ? "." : ", negating."));
        result = (op == 0);
    }

    debugs(28, 4, (op ? null_string : "!") << _acl->name << " result is " <<
           (result ? "true" : "false"));
    return result;
}