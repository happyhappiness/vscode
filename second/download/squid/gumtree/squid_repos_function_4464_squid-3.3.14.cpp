bool
ACLUserData::empty() const
{
    return names->empty() && !flags.required;
}