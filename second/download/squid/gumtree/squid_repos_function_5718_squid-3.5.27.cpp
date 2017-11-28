int
ACLMaxUserIP::match(ACLChecklist *cl)
{
    ACLFilledChecklist *checklist = Filled(cl);
    allow_t answer = AuthenticateAcl(checklist);
    int ti;

    // convert to tri-state ACL match 1,0,-1
    switch (answer) {
    case ACCESS_ALLOWED:
        // check for a match
        ti = match(checklist->auth_user_request, checklist->src_addr);
        checklist->auth_user_request = NULL;
        return ti;

    case ACCESS_DENIED:
        return 0; // non-match

    case ACCESS_DUNNO:
    case ACCESS_AUTH_REQUIRED:
    default:
        // If the answer is not allowed or denied (matches/not matches) and
        // async authentication is not in progress, then we are done.
        if (checklist->keepMatching())
            checklist->markFinished(answer, "AuthenticateAcl exception");
        return -1; // other
    }
}