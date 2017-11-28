bool
ACLUserData::empty() const
{
    debugs(28,6,"required: " << flags.required << ", number of users: " << userDataNames.size());
    if (flags.required)
        return false;
    return userDataNames.empty();
}