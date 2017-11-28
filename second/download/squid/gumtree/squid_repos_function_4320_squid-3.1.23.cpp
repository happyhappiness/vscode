int
ACLChecklist::fastCheck()
{
    PROF_start(aclCheckFast);
    currentAnswer(ACCESS_DENIED);
    debugs(28, 5, "aclCheckFast: list: " << accessList);
    const acl_access *acl = cbdataReference(accessList);
    while (acl != NULL && cbdataReferenceValid(acl)) {
        currentAnswer(acl->allow);
        if (matchAclListFast(acl->aclList)) {
            PROF_stop(aclCheckFast);
            cbdataReferenceDone(acl);
            return currentAnswer() == ACCESS_ALLOWED;
        }

        /*
         * Reference the next access entry
         */
        const acl_access *A = acl;
        acl = cbdataReference(acl->next);
        cbdataReferenceDone(A);
    }

    debugs(28, 5, "aclCheckFast: no matches, returning: " << (currentAnswer() == ACCESS_DENIED));

    PROF_stop(aclCheckFast);
    return currentAnswer() == ACCESS_DENIED;
}