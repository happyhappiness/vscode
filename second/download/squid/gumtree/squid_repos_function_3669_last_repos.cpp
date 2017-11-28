bool Adaptation::Icap::ServiceRep::availableForOld() const
{
    Must(up());

    int available = availableConnections();
    return (available != 0); // it is -1 (no limit) or has available slots
}