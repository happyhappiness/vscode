bool
ACLChecklist::bannedAction(const allow_t &action) const
{
    const bool found = std::find(bannedActions_.begin(), bannedActions_.end(), action) != bannedActions_.end();
    debugs(28, 5, "Action '" << action << "/" << action.kind << (found ? "' is " : "' is not") << " banned");
    return found;
}