int
ACL::checklistMatches(ACLChecklist *checklist)
{
    int rv;

    if (!checklist->hasRequest() && requiresRequest()) {
        debugs(28, DBG_IMPORTANT, "ACL::checklistMatches WARNING: '" << name << "' ACL is used but there is no HTTP request -- not matching.");
        return 0;
    }

    if (!checklist->hasReply() && requiresReply()) {
        debugs(28, DBG_IMPORTANT, "ACL::checklistMatches WARNING: '" << name << "' ACL is used but there is no HTTP reply -- not matching.");
        return 0;
    }

    debugs(28, 3, "ACL::checklistMatches: checking '" << name << "'");
    rv= match(checklist);
    debugs(28, 3, "ACL::ChecklistMatches: result for '" << name << "' is " << rv);
    return rv;
}