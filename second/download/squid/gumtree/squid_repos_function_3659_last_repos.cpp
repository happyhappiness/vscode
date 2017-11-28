void Adaptation::Icap::ServiceRep::setMaxConnections()
{
    if (cfg().maxConn >= 0)
        theMaxConnections = cfg().maxConn;
    else if (theOptions && theOptions->max_connections >= 0)
        theMaxConnections = theOptions->max_connections;
    else {
        theMaxConnections = -1;
        return;
    }

    if (::Config.workers > 1 )
        theMaxConnections /= ::Config.workers;
}