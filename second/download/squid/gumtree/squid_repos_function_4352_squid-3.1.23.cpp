bool
ACLList::matches (ACLChecklist *checklist) const
{
    assert (_acl);
    AclMatchedName = _acl->name;
    debugs(28, 3, "ACLList::matches: checking " << (op ? null_string : "!") << _acl->name);

    if (_acl->checklistMatches(checklist) != op) {
        debugs(28, 4, "ACLList::matches: result is false");
        return checklist->lastACLResult(false);
    }

    debugs(28, 4, "ACLList::matches: result is true");
    return checklist->lastACLResult(true);
}