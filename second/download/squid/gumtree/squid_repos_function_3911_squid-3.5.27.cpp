void
Adaptation::AccessCheck::check()
{
    debugs(93, 4, HERE << "start checking");

    typedef AccessRules::iterator ARI;
    for (ARI i = AllRules().begin(); i != AllRules().end(); ++i) {
        AccessRule *r = *i;
        if (isCandidate(*r)) {
            debugs(93, 5, HERE << "check: rule '" << r->id << "' is a candidate");
            candidates.push_back(r->id);
        }
    }

    checkCandidates();
}