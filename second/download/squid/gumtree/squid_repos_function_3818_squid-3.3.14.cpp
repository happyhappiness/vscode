void
Adaptation::AccessCheck::checkCandidates()
{
    debugs(93, 4, HERE << "has " << candidates.size() << " rules");

    while (!candidates.empty()) {
        if (AccessRule *r = FindRule(topCandidate())) {
            /* BUG 2526: what to do when r->acl is empty?? */
            // XXX: we do not have access to conn->rfc931 here.
            acl_checklist = new ACLFilledChecklist(r->acl, filter.request, dash_str);
            acl_checklist->reply = filter.reply ? HTTPMSGLOCK(filter.reply) : NULL;
            acl_checklist->nonBlockingCheck(AccessCheckCallbackWrapper, this);
            return;
        }

        candidates.shift(); // the rule apparently went away (reconfigure)
    }

    debugs(93, 4, HERE << "NO candidates left");
    callBack(NULL);
    Must(done());
}