Adaptation::ServiceGroupPointer
Adaptation::AccessCheck::topGroup() const
{
    ServiceGroupPointer g;
    if (candidates.size()) {
        if (AccessRule *r = FindRule(topCandidate())) {
            g = FindGroup(r->groupId);
            debugs(93,5, HERE << "top group for " << r->id << " is " << g);
        } else {
            debugs(93,5, HERE << "no rule for " << topCandidate());
        }
    } else {
        debugs(93,5, HERE << "no candidates"); // should not happen
    }

    return g;
}