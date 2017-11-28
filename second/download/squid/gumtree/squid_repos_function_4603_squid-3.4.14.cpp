bool
ACLChecklist::prepNonBlocking()
{
    assert(accessList);

    if (callerGone()) {
        checkCallback(ACCESS_DUNNO); // the answer does not really matter
        return false;
    }

    /** \par
     * If the accessList is no longer valid (i.e. its been
     * freed because of a reconfigure), then bail with ACCESS_DUNNO.
     */

    if (!cbdataReferenceValid(accessList)) {
        cbdataReferenceDone(accessList);
        debugs(28, 4, "ACLChecklist::check: " << this << " accessList is invalid");
        checkCallback(ACCESS_DUNNO);
        return false;
    }

    return true;
}