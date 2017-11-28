allow_t const &
ACLChecklist::fastCheck()
{
    PROF_start(aclCheckFast);

    preCheck("fast rules");
    asyncCaller_ = false;

    debugs(28, 5, "aclCheckFast: list: " << accessList);
    const Acl::Tree *acl = cbdataReference(accessList);
    if (acl != NULL && cbdataReferenceValid(acl)) {
        matchAndFinish(); // calls markFinished() on success

        // if finished (on a match or in exceptional cases), stop
        if (finished()) {
            cbdataReferenceDone(acl);
            occupied_ = false;
            PROF_stop(aclCheckFast);
            return currentAnswer();
        }

        // fall through for mismatch handling
    }

    // There were no rules to match or no rules matched
    calcImplicitAnswer();
    cbdataReferenceDone(acl);
    occupied_ = false;
    PROF_stop(aclCheckFast);

    return currentAnswer();
}