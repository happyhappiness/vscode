int
ACLProxyAuth::match(ACLChecklist *checklist)
{
    allow_t answer = AuthenticateAcl(checklist);

    // convert to tri-state ACL match 1,0,-1
    switch (answer) {
    case ACCESS_ALLOWED:
        // check for a match
        return matchProxyAuth(checklist);

    case ACCESS_DENIED:
        return 0; // non-match

    case ACCESS_DUNNO:
    case ACCESS_AUTH_REQUIRED:
    default:
        // If the answer is not allowed or denied (matches/not matches) and
        // async authentication is not needed (asyncNeeded), then we are done.
        if (!checklist->asyncNeeded())
            checklist->markFinished(answer, "AuthenticateAcl exception");
        return -1; // other
    }
}