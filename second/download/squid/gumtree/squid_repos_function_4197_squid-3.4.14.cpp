bool Adaptation::Icap::ServiceRep::allows204() const
{
    Must(hasOptions());
    return true; // in the future, we may have ACLs to prevent 204s
}