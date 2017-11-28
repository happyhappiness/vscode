bool
ACLChecklist::asyncNeeded() const
{
    return state_ != NullState::Instance();
}