allow_t const &
ACLChecklist::fastCheck()
{
    PROF_start(aclCheckFast);

    preCheck("fast rules");

    allow_t lastSeenKeyword = ACCESS_DUNNO;
    debugs(28, 5, "aclCheckFast: list: " << accessList);
    const acl_access *acl = cbdataReference(accessList);
    while (acl != NULL && cbdataReferenceValid(acl)) {
        // on a match, finish
        if (matchAclList(acl->aclList, true))
            markFinished(acl->allow, "first matching rule won");

        // if finished (on a match or in exceptional cases), stop
        if (finished()) {
            cbdataReferenceDone(acl);
            PROF_stop(aclCheckFast);
            return currentAnswer();
        }

        // on a mismatch, try the next access rule
        lastSeenKeyword = acl->allow;
        const acl_access *A = acl;
        acl = cbdataReference(acl->next);
        cbdataReferenceDone(A);
    }

    // There were no rules to match or no rules matched
    calcImplicitAnswer(lastSeenKeyword);
    PROF_stop(aclCheckFast);

    return currentAnswer();
}