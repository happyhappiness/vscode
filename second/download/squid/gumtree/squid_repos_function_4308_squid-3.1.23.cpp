void
ACLChecklist::preCheck()
{
    debugs(28, 3, "ACLChecklist::preCheck: " << this << " checking '" << accessList->cfgline << "'");
    /* what is our result on a match? */
    currentAnswer(accessList->allow);
}