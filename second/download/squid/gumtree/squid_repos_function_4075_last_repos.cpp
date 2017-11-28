inline const char *
AllowOrDeny(const allow_t &action)
{
    return action.allowed() ? "allow" : "deny";
}