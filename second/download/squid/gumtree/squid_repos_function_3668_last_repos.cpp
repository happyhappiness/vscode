bool Adaptation::Icap::ServiceRep::availableForNew() const
{
    Must(up());
    int available = availableConnections();
    if (available < 0)
        return true;
    else
        return (available - theAllWaiters > 0);
}