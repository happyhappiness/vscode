void
ACLChecklist::NullState::checkForAsync(ACLChecklist *) const
{
    assert(false); // or the Checklist will never get out of the async state
}