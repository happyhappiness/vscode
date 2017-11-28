 *
 * NP: this should probably be made Async now.
 */
void
ACLChecklist::nonBlockingCheck(ACLCB * callback_, void *callback_data_)
{
    callback = callback_;
    callback_data = cbdataReference(callback_data_);
    matchNonBlocking();
}

allow_t const &
ACLChecklist::fastCheck(const ACLList * list)
{
    PROF_start(aclCheckFast);
    currentAnswer(ACCESS_DUNNO);
    matchAclList(list, true);
    // assume ALLOWED on matches due to not having an acl_access object
    if (finished())
        currentAnswer(ACCESS_ALLOWED);
    PROF_stop(aclCheckFast);
    return currentAnswer();
}

/* Warning: do not cbdata lock this here - it
 * may be static or on the stack
 */
allow_t const &
ACLChecklist::fastCheck()
{
    PROF_start(aclCheckFast);
    currentAnswer(ACCESS_DUNNO);

    debugs(28, 5, "aclCheckFast: list: " << accessList);
    const acl_access *acl = cbdataReference(accessList);
    while (acl != NULL && cbdataReferenceValid(acl)) {
        matchAclList(acl->aclList, true);
        if (finished()) {
            currentAnswer(acl->allow);
            PROF_stop(aclCheckFast);
            cbdataReferenceDone(acl);
            return currentAnswer();
        }

        /*
         * Reference the next access entry
         */
        const acl_access *A = acl;
        acl = cbdataReference(acl->next);
        cbdataReferenceDone(A);
    }

    debugs(28, 5, "aclCheckFast: no matches, returning: " << currentAnswer());
    PROF_stop(aclCheckFast);

    return currentAnswer();
}


bool
ACLChecklist::checking() const
{
    return checking_;
}
