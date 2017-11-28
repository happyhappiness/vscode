int
ACLExternal::match(ACLChecklist *checklist)
{
    allow_t answer = aclMatchExternal(data, Filled(checklist));

    // convert to tri-state ACL match 1,0,-1
    switch (answer) {
    case ACCESS_ALLOWED:
        return 1; // match

    case ACCESS_DENIED:
        return 0; // non-match

    case ACCESS_DUNNO:
    case ACCESS_AUTH_REQUIRED:
    default:
        // If the answer is not allowed or denied (matches/not matches) and
        // async authentication is not needed (asyncNeeded), then we are done.
        if (!checklist->asyncNeeded())
            checklist->markFinished(answer, "aclMatchExternal exception");
        return -1; // other
    }
}