bool Adaptation::Icap::ServiceRep::up() const
{
    return !isSuspended && hasOptions();
}