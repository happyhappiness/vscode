void
ACLChecklist::banAction(const allow_t &action)
{
    bannedActions_.push_back(action);
}