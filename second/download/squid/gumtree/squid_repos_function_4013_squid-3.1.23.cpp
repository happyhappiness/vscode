void
Adaptation::Icap::ServiceRep::finalize()
{
    Adaptation::Service::finalize();

    // use /etc/services or default port if needed
    const bool have_port = cfg().port >= 0;
    if (!have_port) {
        struct servent *serv = getservbyname("icap", "tcp");

        if (serv) {
            writeableCfg().port = htons(serv->s_port);
        } else {
            writeableCfg().port = 1344;
        }
    }
}