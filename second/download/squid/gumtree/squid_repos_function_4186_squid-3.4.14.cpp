int Adaptation::Icap::ServiceRep::excessConnections() const
{
    if (theMaxConnections < 0)
        return 0;

    // Waiters affect the number of needed connections but a needed
    // connection may still be excessive from Max-Connections p.o.v.
    // so we should not account for waiting transaction needs here.
    const int debt =  theBusyConns + theIdleConns->count() - theMaxConnections;
    if (debt > 0)
        return debt;
    else
        return 0;
}