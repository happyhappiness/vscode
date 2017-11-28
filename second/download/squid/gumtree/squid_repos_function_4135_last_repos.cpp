allow_t const &
ACLChecklist::fastCheck(const Acl::Tree * list)
{
    PROF_start(aclCheckFast);

    preCheck("fast ACLs");
    asyncCaller_ = false;

    // Concurrent checks are not supported, but sequential checks are, and they
    // may use a mixture of fastCheck(void) and fastCheck(list) calls.
    const Acl::Tree * const savedList = changeAcl(list);

    // assume DENY/ALLOW on mis/matches due to action-free accessList
    // matchAndFinish() takes care of the ALLOW case
    if (accessList && cbdataReferenceValid(accessList))
        matchAndFinish(); // calls markFinished() on success
    if (!finished())
        markFinished(ACCESS_DENIED, "ACLs failed to match");

    changeAcl(savedList);
    occupied_ = false;
    PROF_stop(aclCheckFast);
    return currentAnswer();
}