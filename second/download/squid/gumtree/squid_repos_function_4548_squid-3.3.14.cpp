void
ACLChecklist::markFinished(const allow_t &finalAnswer, const char *reason)
{
    assert (!finished() && !asyncInProgress());
    finished_ = true;
    allow_ = finalAnswer;
    debugs(28, 3, HERE << this << " answer " << allow_ << " for " << reason);
}