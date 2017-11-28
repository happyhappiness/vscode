void
ACLChecklist::check()
{
    if (checking())
        return;

    /** Deny if no rules present. */
    currentAnswer(ACCESS_DENIED);

    if (callerGone()) {
        checkCallback(currentAnswer());
        return;
    }

    /** The ACL List should NEVER be NULL when calling this method.
     * Always caller should check for NULL and handle appropriate to its needs first.
     * We cannot select a sensible default for all callers here. */
    if (accessList == NULL) {
        debugs(28, DBG_CRITICAL, "SECURITY ERROR: ACL " << this << " checked with nothing to match against!!");
        currentAnswer(ACCESS_DENIED);
        checkCallback(currentAnswer());
        return;
    }

    /* NOTE: This holds a cbdata reference to the current access_list
     * entry, not the whole list.
     */
    while (accessList != NULL) {
        /** \par
         * If the _acl_access is no longer valid (i.e. its been
         * freed because of a reconfigure), then bail on this
         * access check.  For now, return ACCESS_DENIED.
         */

        if (!cbdataReferenceValid(accessList)) {
            cbdataReferenceDone(accessList);
            debugs(28, 4, "ACLChecklist::check: " << this << " accessList is invalid");
            continue;
        }

        checking (true);
        checkAccessList();
        checking (false);

        if (asyncInProgress()) {
            return;
        }

        if (finished()) {
            /** \par
             * Either the request is allowed, denied, requires authentication.
             */
            debugs(28, 3, "ACLChecklist::check: " << this << " match found, calling back with " << currentAnswer());
            cbdataReferenceDone(accessList); /* A */
            checkCallback(currentAnswer());
            /* From here on in, this may be invalid */
            return;
        }

        /*
         * Reference the next access entry
         */
        const acl_access *A = accessList;

        assert (A);

        accessList = cbdataReference(A->next);

        cbdataReferenceDone(A);
    }

    /** If dropped off the end of the list return inversion of last line allow/deny action. */
    debugs(28, 3, HERE << this << " NO match found, returning " <<
           (currentAnswer() != ACCESS_DENIED ? ACCESS_DENIED : ACCESS_ALLOWED));

    checkCallback(currentAnswer() != ACCESS_DENIED ? ACCESS_DENIED : ACCESS_ALLOWED);
}