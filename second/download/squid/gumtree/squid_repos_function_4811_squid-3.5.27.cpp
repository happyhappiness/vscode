void
ACLChecklist::calcImplicitAnswer()
{
    const allow_t lastAction = (accessList && cbdataReferenceValid(accessList)) ?
                               accessList->lastAction() : allow_t(ACCESS_DUNNO);
    allow_t implicitRuleAnswer = ACCESS_DUNNO;
    if (lastAction == ACCESS_DENIED) // reverse last seen "deny"
        implicitRuleAnswer = ACCESS_ALLOWED;
    else if (lastAction == ACCESS_ALLOWED) // reverse last seen "allow"
        implicitRuleAnswer = ACCESS_DENIED;
    // else we saw no rules and will respond with ACCESS_DUNNO

    debugs(28, 3, HERE << this << " NO match found, last action " <<
           lastAction << " so returning " << implicitRuleAnswer);
    markFinished(implicitRuleAnswer, "implicit rule won");
}