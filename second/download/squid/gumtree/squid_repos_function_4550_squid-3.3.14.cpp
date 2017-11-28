void
ACLChecklist::checkAccessList()
{
    debugs(28, 3, HERE << this << " checking '" << accessList->cfgline << "'");
    /* does the current AND clause match */
    if (matchAclList(accessList->aclList, false))
        markFinished(accessList->allow, "first matching rule won");

    // If we are not finished() here, the caller must distinguish between
    // slow async calls and pure rule mismatches using asyncInProgress().
}