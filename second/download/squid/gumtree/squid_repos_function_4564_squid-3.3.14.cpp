void
ACLChecklist::calcImplicitAnswer(const allow_t &lastSeenAction)
{
    allow_t implicitRuleAnswer = ACCESS_DUNNO;
    if (lastSeenAction == ACCESS_DENIED) // reverse last seen "deny"
        implicitRuleAnswer = ACCESS_ALLOWED;
    else if (lastSeenAction == ACCESS_ALLOWED) // reverse last seen "allow"
        implicitRuleAnswer = ACCESS_DENIED;
    // else we saw no rules and will respond with ACCESS_DUNNO

    debugs(28, 3, HERE << this << " NO match found, last action " <<
           lastSeenAction << " so returning " << implicitRuleAnswer);
    markFinished(implicitRuleAnswer, "implicit rule won");
}