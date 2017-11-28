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

/// When no rules matched, the answer is the inversion of the last rule
/// action (or ACCESS_DUNNO if the reversal is not possible).
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

bool
ACLChecklist::callerGone()
{
    return !cbdataReferenceValid(callback_data);
}
