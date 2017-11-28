void
ACLChecklist::AsyncState::changeState (ACLChecklist *checklist, AsyncState *newState) const
{
    checklist->changeState(newState);
}