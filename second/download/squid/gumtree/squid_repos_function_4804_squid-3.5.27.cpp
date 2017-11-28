void
ACLChecklist::changeState (AsyncState *newState)
{
    /* only change from null to active and back again,
     * not active to active.
     * relax this once conversion to states is complete
     * RBC 02 2003
     */
    assert (state_ == NullState::Instance() || newState == NullState::Instance());
    state_ = newState;
}