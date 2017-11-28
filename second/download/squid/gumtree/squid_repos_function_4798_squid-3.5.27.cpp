void
ACLChecklist::preCheck(const char *what)
{
    debugs(28, 3, HERE << this << " checking " << what);

    // concurrent checks using the same Checklist are not supported
    assert(!occupied_);
    occupied_ = true;
    asyncLoopDepth_ = 0;

    AclMatchedName = NULL;
    finished_ = false;
}