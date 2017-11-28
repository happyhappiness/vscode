bool
Adaptation::AccessCheck::isCandidate(AccessRule &r)
{
    debugs(93,7,HERE << "checking candidacy of " << r.id << ", group " <<
           r.groupId);

    ServiceGroupPointer g = FindGroup(r.groupId);

    if (!g) {
        debugs(93,7,HERE << "lost " << r.groupId << " group in rule" << r.id);
        return false;
    }

    const bool wants = g->wants(filter);
    debugs(93,7,HERE << r.groupId << (wants ? " wants" : " ignores"));
    return wants;
}